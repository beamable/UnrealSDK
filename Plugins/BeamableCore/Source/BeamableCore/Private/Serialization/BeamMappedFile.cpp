#include "Serialization/BeamMappedFile.h"

#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/PlatformAtomics.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/Paths.h"

// -----------------------------------------------------------------------------
// Platform-specific mmap headers.
//
// We deliberately use the OS APIs directly because UE's IMappedFileHandle is
// read-only and there's no cross-platform writable-mmap helper in the engine.
// All platform branches are confined to this single .cpp; the public header
// stays platform-agnostic via the opaque `void* PlatformHandle` member.
// -----------------------------------------------------------------------------
#if PLATFORM_WINDOWS
	#include "Windows/AllowWindowsPlatformTypes.h"
	#include <windows.h>
	#include "Windows/HideWindowsPlatformTypes.h"
#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_UNIX || PLATFORM_IOS || PLATFORM_ANDROID
	#include <sys/mman.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <errno.h>
#endif

DEFINE_LOG_CATEGORY_STATIC(LogBeamMappedFile, Log, All);


namespace BeamMappedFile
{
	// =========================================================================
	// Required header layout
	// =========================================================================
	//
	// The first 16 bytes of every file we manage are owned by the utility.
	// Layout:
	//
	//   offset 0:  uint32 Magic        (caller-specified at Open time)
	//   offset 4:  uint32 Version      (caller-specified at Open time)
	//   offset 8:  int32  Head         (atomic; absolute file offset of next ring write)
	//   offset 12: int32  Reserved     (zeroed; reserved for future use)
	//
	// We don't actually expose this as a struct — there's no need; the offsets
	// are constants and we read/write through them.

	namespace
	{
		constexpr int64 OffsetMagic    = 0;
		constexpr int64 OffsetVersion  = 4;
		constexpr int64 OffsetHead     = 8;
		constexpr int64 OffsetReserved = 12;
	}

	const int32  RequiredHeaderSize = 16;
	const uint32 RingSlotOverhead   = sizeof(uint32) + sizeof(uint8);


	// =========================================================================
	// Internal helpers
	// =========================================================================

	namespace
	{
		/// Per-file platform handles. Owned by `FBeamMappedFile::PlatformHandle`
		/// (allocated in Open, deleted in Close). Never escapes this .cpp.
		struct FPlatformState
		{
#if PLATFORM_WINDOWS
			HANDLE FileHandle    = INVALID_HANDLE_VALUE;
			HANDLE MappingHandle = nullptr;
#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_UNIX || PLATFORM_IOS || PLATFORM_ANDROID
			int Fd = -1;
#endif
		};

		// --- Atomic ops on int32 fields inside the mapping (file-private) ---

		int32 LoadHead(const FBeamMappedFile& File)
		{
			volatile int32* Ptr = reinterpret_cast<volatile int32*>(const_cast<uint8*>(File.Data) + OffsetHead);
			return FPlatformAtomics::AtomicRead(Ptr);
		}

		bool CasHead(FBeamMappedFile& File, int32 Expected, int32 Desired)
		{
			volatile int32* Ptr = reinterpret_cast<volatile int32*>(File.Data + OffsetHead);
			return FPlatformAtomics::InterlockedCompareExchange(Ptr, Desired, Expected) == Expected;
		}

		void StoreHead(FBeamMappedFile& File, int32 Value)
		{
			volatile int32* Ptr = reinterpret_cast<volatile int32*>(File.Data + OffsetHead);
			FPlatformAtomics::InterlockedExchange(Ptr, Value);
		}

		// --- Required header validation + stamping ---

		bool ValidateRequiredHeader(const FBeamMappedFile& File, uint32 ExpectedMagic, uint32 ExpectedVersion)
		{
			if (File.Size < RequiredHeaderSize) return false;
			uint32 OnDiskMagic = 0, OnDiskVersion = 0;
			FMemory::Memcpy(&OnDiskMagic,   File.Data + OffsetMagic,   sizeof(uint32));
			FMemory::Memcpy(&OnDiskVersion, File.Data + OffsetVersion, sizeof(uint32));
			return OnDiskMagic == ExpectedMagic && OnDiskVersion == ExpectedVersion;
		}

		void WriteFreshRequiredHeader(FBeamMappedFile& File, uint32 Magic, uint32 Version, int64 BodyStart)
		{
			FMemory::Memcpy(File.Data + OffsetMagic,    &Magic,        sizeof(uint32));
			FMemory::Memcpy(File.Data + OffsetVersion,  &Version,      sizeof(uint32));
			const int32 InitialHead = static_cast<int32>(BodyStart);
			const int32 Zero = 0;
			FMemory::Memcpy(File.Data + OffsetHead,     &InitialHead,  sizeof(int32));
			FMemory::Memcpy(File.Data + OffsetReserved, &Zero,         sizeof(int32));
		}

		// Body region helpers — derived from the file layout, not stored.
		int64 BodyStartOffset(const FBeamMappedFile& File) { return RequiredHeaderSize + File.ExtraHeaderBytes; }
		int64 BodyEndOffset  (const FBeamMappedFile& File) { return File.Size; }
	}


	// =========================================================================
	// 1. Lifecycle
	// =========================================================================

	bool Open(FBeamMappedFile& Out, const FString& Path, int64 Capacity,
	          uint32 ExpectedMagic, uint32 ExpectedVersion,
	          int32 ExtraHeaderBytes, bool& bOutWasReset)
	{
		// Reset whatever the caller passed in so a failed Open leaves Out in
		// the same shape as a default-constructed value.
		Close(Out);
		bOutWasReset = false;

		if (Capacity <= 0)
		{
			UE_LOG(LogBeamMappedFile, Error, TEXT("BeamMappedFile::Open: non-positive capacity %lld"), Capacity);
			return false;
		}
		if (ExtraHeaderBytes < 0)
		{
			UE_LOG(LogBeamMappedFile, Error, TEXT("BeamMappedFile::Open: negative ExtraHeaderBytes %d"), ExtraHeaderBytes);
			return false;
		}
		const int64 BodyStart = (int64)RequiredHeaderSize + ExtraHeaderBytes;
		if (Capacity < BodyStart + (int64)RingSlotOverhead)
		{
			UE_LOG(LogBeamMappedFile, Error,
				TEXT("BeamMappedFile::Open: capacity %lld too small (need at least %lld for headers + a single empty slot)"),
				Capacity, BodyStart + (int64)RingSlotOverhead);
			return false;
		}

		// Make sure the parent directory exists; the platform calls won't create it.
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		const FString Dir = FPaths::GetPath(Path);
		if (!Dir.IsEmpty() && !PlatformFile.DirectoryExists(*Dir))
		{
			PlatformFile.CreateDirectoryTree(*Dir);
		}

		FPlatformState* State = new FPlatformState();
		uint8* MappedPtr = nullptr;

#if PLATFORM_WINDOWS
		// 1) Open the file (creating if needed). FILE_SHARE_READ lets other
		//    processes open it for read concurrently — useful for diagnostics.
		State->FileHandle = ::CreateFileW(*Path,
			GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
			nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (State->FileHandle == INVALID_HANDLE_VALUE)
		{
			UE_LOG(LogBeamMappedFile, Error, TEXT("CreateFile failed for '%s' (err=%lu)"), *Path, ::GetLastError());
			delete State;
			return false;
		}

		// 2) CreateFileMapping with a size larger than the file extends the file
		//    up to that size. Size smaller than the file is allowed — the mapping
		//    just covers the first `Capacity` bytes; the file is NOT truncated.
		const DWORD HighSize = static_cast<DWORD>(Capacity >> 32);
		const DWORD LowSize  = static_cast<DWORD>(Capacity & 0xFFFFFFFFull);
		State->MappingHandle = ::CreateFileMappingW(State->FileHandle,
			nullptr, PAGE_READWRITE, HighSize, LowSize, nullptr);
		if (!State->MappingHandle)
		{
			UE_LOG(LogBeamMappedFile, Error, TEXT("CreateFileMapping failed for '%s' (err=%lu)"), *Path, ::GetLastError());
			::CloseHandle(State->FileHandle);
			delete State;
			return false;
		}

		// 3) Map the view read+write.
		MappedPtr = static_cast<uint8*>(::MapViewOfFile(State->MappingHandle,
			FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, static_cast<SIZE_T>(Capacity)));
		if (!MappedPtr)
		{
			UE_LOG(LogBeamMappedFile, Error, TEXT("MapViewOfFile failed for '%s' (err=%lu)"), *Path, ::GetLastError());
			::CloseHandle(State->MappingHandle);
			::CloseHandle(State->FileHandle);
			delete State;
			return false;
		}

#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_UNIX || PLATFORM_IOS || PLATFORM_ANDROID
		// 1) Open / create the file.
		const FTCHARToUTF8 PathC(*Path);
		State->Fd = ::open(PathC.Get(), O_RDWR | O_CREAT, 0644);
		if (State->Fd < 0)
		{
			UE_LOG(LogBeamMappedFile, Error, TEXT("open() failed for '%s' (errno=%d)"), *Path, errno);
			delete State;
			return false;
		}

		// 2) Extend (but never truncate) the file to Capacity. ftruncate would
		//    shrink a larger file; we don't want that, so check size first.
		struct stat St = {};
		if (::fstat(State->Fd, &St) != 0)
		{
			UE_LOG(LogBeamMappedFile, Error, TEXT("fstat() failed for '%s' (errno=%d)"), *Path, errno);
			::close(State->Fd);
			delete State;
			return false;
		}
		if ((int64)St.st_size < Capacity)
		{
			if (::ftruncate(State->Fd, static_cast<off_t>(Capacity)) != 0)
			{
				UE_LOG(LogBeamMappedFile, Error, TEXT("ftruncate() failed for '%s' (errno=%d)"), *Path, errno);
				::close(State->Fd);
				delete State;
				return false;
			}
		}

		// 3) Map the file read+write. MAP_SHARED so writes are visible to other
		//    processes mapping the same file (and survive across our process exit).
		void* MR = ::mmap(nullptr, static_cast<size_t>(Capacity),
			PROT_READ | PROT_WRITE, MAP_SHARED, State->Fd, 0);
		if (MR == MAP_FAILED)
		{
			UE_LOG(LogBeamMappedFile, Error, TEXT("mmap() failed for '%s' (errno=%d)"), *Path, errno);
			::close(State->Fd);
			delete State;
			return false;
		}
		MappedPtr = static_cast<uint8*>(MR);

#else
		UE_LOG(LogBeamMappedFile, Error, TEXT("BeamMappedFile: writable mmap not supported on this platform."));
		delete State;
		return false;
#endif

		Out.Data             = MappedPtr;
		Out.Size             = Capacity;
		Out.ExtraHeaderBytes = ExtraHeaderBytes;
		Out.PlatformHandle   = State;
		Out.Path             = Path;

		// Validate the required header. Mismatch (including a fresh all-zero
		// file) → wipe everything and stamp a fresh required header.
		if (!ValidateRequiredHeader(Out, ExpectedMagic, ExpectedVersion))
		{
			FMemory::Memzero(Out.Data, Out.Size);
			WriteFreshRequiredHeader(Out, ExpectedMagic, ExpectedVersion, BodyStart);
			bOutWasReset = true;
		}
		return true;
	}

	void Close(FBeamMappedFile& File)
	{
		if (File.PlatformHandle)
		{
			FPlatformState* State = static_cast<FPlatformState*>(File.PlatformHandle);

#if PLATFORM_WINDOWS
			if (File.Data)              ::UnmapViewOfFile(File.Data);
			if (State->MappingHandle)   ::CloseHandle(State->MappingHandle);
			if (State->FileHandle != INVALID_HANDLE_VALUE) ::CloseHandle(State->FileHandle);
#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_UNIX || PLATFORM_IOS || PLATFORM_ANDROID
			if (File.Data)        ::munmap(File.Data, static_cast<size_t>(File.Size));
			if (State->Fd >= 0)   ::close(State->Fd);
#endif
			delete State;
		}

		File.Data             = nullptr;
		File.Size             = 0;
		File.ExtraHeaderBytes = 0;
		File.PlatformHandle   = nullptr;
		File.Path.Reset();
	}

	bool  IsOpen(const FBeamMappedFile& File) { return File.Data != nullptr; }
	int64 Size  (const FBeamMappedFile& File) { return File.Size; }

	void Sync(FBeamMappedFile& File, int64 Offset, int64 NumBytes)
	{
		if (!File.Data) return;
		if (NumBytes <= 0) return;
		if (Offset < 0 || Offset + NumBytes > File.Size) return;

#if PLATFORM_WINDOWS
		::FlushViewOfFile(File.Data + Offset, static_cast<SIZE_T>(NumBytes));
#elif PLATFORM_LINUX || PLATFORM_MAC || PLATFORM_UNIX || PLATFORM_IOS || PLATFORM_ANDROID
		::msync(File.Data + Offset, static_cast<size_t>(NumBytes), MS_SYNC);
#endif
	}


	// =========================================================================
	// 2. Extra header
	// =========================================================================

	uint8*       ExtraHeader    (FBeamMappedFile& File)       { return IsOpen(File) ? File.Data + RequiredHeaderSize : nullptr; }
	const uint8* ExtraHeader    (const FBeamMappedFile& File) { return IsOpen(File) ? File.Data + RequiredHeaderSize : nullptr; }
	int32        ExtraHeaderSize(const FBeamMappedFile& File) { return File.ExtraHeaderBytes; }


	// =========================================================================
	// 3. Ring buffer
	// =========================================================================
	//
	// Slot format (within the body):
	//
	//   [u32 PayloadLen] [bytes Payload[PayloadLen]] [u8 Committed]
	//
	// The head field stores the absolute next-write file offset (>= BodyStart,
	// <= BodyEnd). All writes go directly to the mapped pointer — no syscalls,
	// no fsync, no in-memory mirror. The OS handles page-cache persistence.

	bool RingAppend(FBeamMappedFile& File, const TArray<uint8>& Payload)
	{
		if (!IsOpen(File)) return false;

		const int64 BodyStart = BodyStartOffset(File);
		const int64 BodyEnd   = BodyEndOffset(File);
		if (BodyStart >= BodyEnd) return false;

		const uint32 Need = static_cast<uint32>(Payload.Num()) + RingSlotOverhead;

		// CAS-claim a [Offset, Offset+Need) byte range. Loops on contention; bails
		// on overflow.
		int64 Offset;
		for (;;)
		{
			const int32 Expected = LoadHead(File);
			const int64 ExpectedAbs = Expected;
			if (ExpectedAbs + (int64)Need > BodyEnd) return false;
			const int32 Desired = static_cast<int32>(ExpectedAbs + Need);
			if (CasHead(File, Expected, Desired))
			{
				Offset = ExpectedAbs;
				break;
			}
		}

		// Now we own [Offset, Offset+Need) exclusively. Write length prefix +
		// payload directly into the mapped region — no syscall, just pointer writes.
		uint8* Slot = File.Data + Offset;
		const uint32 PayloadLen = static_cast<uint32>(Payload.Num());
		FMemory::Memcpy(Slot, &PayloadLen, sizeof(uint32));
		FMemory::Memcpy(Slot + sizeof(uint32), Payload.GetData(), PayloadLen);

		// Release-store the commit byte. Any drainer that sees commit=1 also
		// sees the fully written payload (full-barrier from FPlatformAtomics).
		volatile int8* Commit = reinterpret_cast<int8*>(Slot + sizeof(uint32) + PayloadLen);
		FPlatformAtomics::InterlockedExchange(Commit, (int8)1);
		return true;
	}

	void RingDrain(FBeamMappedFile& File, TArray<TArray<uint8>>& Out)
	{
		Out.Reset();
		if (!IsOpen(File)) return;

		const int64 BodyStart = BodyStartOffset(File);
		const int64 BodyEnd   = BodyEndOffset(File);
		if (BodyStart >= BodyEnd) return;

		// CAS-reset Head to BodyStart, capturing the prior value as our snapshot end.
		// Producers that lose the race retry against the new (smaller) head and
		// land at the start of the cleared region.
		int32 OldHead;
		for (;;)
		{
			OldHead = LoadHead(File);
			if (OldHead <= BodyStart) return;
			if (CasHead(File, OldHead, static_cast<int32>(BodyStart))) break;
		}

		// Walk slots in [BodyStart, OldHead).
		uint8* B = File.Data;
		int64 Cursor = BodyStart;
		const int64 End = OldHead;
		while (Cursor + (int64)sizeof(uint32) + (int64)sizeof(uint8) <= End)
		{
			uint32 PayloadLen = 0;
			FMemory::Memcpy(&PayloadLen, B + Cursor, sizeof(uint32));
			const int64 SlotEnd = Cursor + (int64)sizeof(uint32) + (int64)PayloadLen + (int64)sizeof(uint8);
			if (SlotEnd > End || SlotEnd > BodyEnd) break;

			if (B[Cursor + sizeof(uint32) + PayloadLen] == 1)
			{
				TArray<uint8>& Slot = Out.AddDefaulted_GetRef();
				Slot.SetNumUninitialized(PayloadLen);
				FMemory::Memcpy(Slot.GetData(), B + Cursor + sizeof(uint32), PayloadLen);
			}
			Cursor = SlotEnd;
		}

		// Zero the consumed range so producers landing here next see fresh state.
		const int64 Cleared = End - BodyStart;
		if (Cleared > 0)
		{
			FMemory::Memzero(B + BodyStart, Cleared);
		}
	}

	void RingReadOnce(const FBeamMappedFile& File, TArray<TArray<uint8>>& Out)
	{
		Out.Reset();
		if (!IsOpen(File)) return;

		const int64 BodyStart = BodyStartOffset(File);
		const int64 BodyEnd   = BodyEndOffset(File);
		if (BodyStart >= BodyEnd) return;

		const uint8* B = File.Data;
		int32 Head = 0;
		FMemory::Memcpy(&Head, B + OffsetHead, sizeof(int32));
		if (Head <= BodyStart) return;

		int64 Cursor = BodyStart;
		const int64 End = FMath::Min<int64>(Head, BodyEnd);
		while (Cursor + (int64)sizeof(uint32) + (int64)sizeof(uint8) <= End)
		{
			uint32 PayloadLen = 0;
			FMemory::Memcpy(&PayloadLen, B + Cursor, sizeof(uint32));
			const int64 SlotEnd = Cursor + (int64)sizeof(uint32) + (int64)PayloadLen + (int64)sizeof(uint8);
			if (SlotEnd > End) break;

			if (B[Cursor + sizeof(uint32) + PayloadLen] == 1)
			{
				TArray<uint8>& Slot = Out.AddDefaulted_GetRef();
				Slot.SetNumUninitialized(PayloadLen);
				FMemory::Memcpy(Slot.GetData(), B + Cursor + sizeof(uint32), PayloadLen);
			}
			Cursor = SlotEnd;
		}
	}

	void RingReset(FBeamMappedFile& File)
	{
		if (!IsOpen(File)) return;

		const int64 BodyStart = BodyStartOffset(File);
		const int64 BodyEnd   = BodyEndOffset(File);
		if (BodyStart >= BodyEnd) return;

		FMemory::Memzero(File.Data + BodyStart, BodyEnd - BodyStart);
		StoreHead(File, static_cast<int32>(BodyStart));
	}
}
