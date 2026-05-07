#pragma once

// =============================================================================
// BeamMappedFile — true writable memory-mapped file utility (cross-platform)
// -----------------------------------------------------------------------------
// Layout
//
//   The file is divided into three regions:
//
//     [Required header  | 16 bytes ] [Extra header | N bytes ] [Body | rest ]
//      Magic                          Caller-defined raw bytes   Ring buffer
//      Version
//      Head (atomic)
//      Reserved
//
//   The required header is owned by this utility — callers never touch its
//   bytes directly. Validation (Magic + Version match) and the atomic Head
//   pointer used by the ring buffer live in there.
//
//   The extra header is owned by the caller — `ExtraHeaderBytes` of raw bytes
//   immediately after the required header. Use it to stash anything you want
//   to live next to the file (SDK version string, custom flags, struct of
//   per-game state, etc.). Access via `ExtraHeader(File)` / `ExtraHeaderSize(File)`.
//
//   The body is the ring buffer. Lock-free CAS-based slot reservation, length-
//   prefixed payloads, per-slot commit byte for torn-write detection.
//
// Backing storage
//
//   The mapped region IS the file. Reads/writes through the returned `Data`
//   pointer go straight into the OS page cache (which is the file). The OS
//   owns persistence: dirty pages survive process crashes (the kernel keeps
//   them in cache after our process dies) and the writeback daemon flushes
//   them to physical storage on its own schedule.
//
//   Implementation:
//     - Windows: CreateFileMapping + MapViewOfFile (PAGE_READWRITE / FILE_MAP_*)
//     - POSIX:   mmap(... PROT_READ | PROT_WRITE, MAP_SHARED ...)
//
//   Platform branches are confined to the .cpp; the public header is
//   platform-agnostic via the opaque `PlatformHandle` field.
//
// Usage
//
//     constexpr uint32 kMagic   = 0xBEA50001u;
//     constexpr uint32 kVersion = 1u;
//
//     struct FMyExtra { char SdkVersion[64]; };
//
//     FBeamMappedFile File;
//     bool bWasReset = false;
//     BeamMappedFile::Open(File, Path, /*Capacity=*/4*1024*1024,
//                          kMagic, kVersion, sizeof(FMyExtra), bWasReset);
//
//     if (bWasReset) {
//         // Fresh file: stamp our extra header.
//         FMyExtra Extra = {};
//         FCStringAnsi::Strcpy(Extra.SdkVersion, sizeof(Extra.SdkVersion), "1.2.3");
//         FMemory::Memcpy(BeamMappedFile::ExtraHeader(File), &Extra, sizeof(Extra));
//     }
//
//     BeamMappedFile::RingAppend(File, MyPayload);
//
// =============================================================================

#include "CoreMinimal.h"

namespace BeamMappedFile
{
	// -------------------------------------------------------------------------
	// State
	// -------------------------------------------------------------------------
	/**
	 * State for one mapped file. After a successful Open, `Data` points into
	 * the mapped region of size `Size`. The required header occupies the first
	 * 16 bytes and is fully owned by the utility — do not write to that area.
	 * The extra header begins at offset 16 and runs for `ExtraHeaderBytes` bytes;
	 * the body (ring buffer) starts immediately after.
	 *
	 * `PlatformHandle` is opaque (Win32 file+mapping HANDLE pair on Windows,
	 * POSIX fd on Linux/Mac/etc). It's only valid between Open and Close.
	 */
	struct BEAMABLECORE_API FBeamMappedFile
	{
		uint8*  Data             = nullptr;   ///< Pointer to the mapped region. nullptr when closed.
		int64   Size             = 0;         ///< Size of the mapped region in bytes.
		int32   ExtraHeaderBytes = 0;         ///< Caller-defined extra header size (passed to Open).
		void*   PlatformHandle   = nullptr;   ///< Opaque platform-specific handle bundle.
		FString Path;                         ///< Absolute file path (diagnostics).
	};

	// -------------------------------------------------------------------------
	// Lifecycle
	// -------------------------------------------------------------------------

	/**
	 * Open or create the file at `Path`. The file is grown to at least `Capacity`
	 * bytes (existing content preserved) and mapped read+write for `Capacity`
	 * bytes starting at offset 0.
	 *
	 * The required header at offset 0 is checked against `ExpectedMagic` and
	 * `ExpectedVersion`. If either differs (including a fresh file with all-zero
	 * bytes), the entire mapping is zeroed, a fresh required header is stamped,
	 * and `bOutWasReset` is set to true. If both match, existing contents are
	 * preserved and `bOutWasReset` is set to false.
	 *
	 * `ExtraHeaderBytes` must be >= 0; zero is allowed (no extra header).
	 *
	 * Returns true on success. On failure, all fields of `Out` are reset.
	 */
	BEAMABLECORE_API bool Open(FBeamMappedFile& Out, const FString& Path, int64 Capacity,
	                           uint32 ExpectedMagic, uint32 ExpectedVersion,
	                           int32 ExtraHeaderBytes, bool& bOutWasReset);

	/**
	 * Unmap the region and release the platform handles. Idempotent.
	 *
	 * Pending writes already issued through `Data` live in the OS page cache and
	 * survive this call. For explicit durability before close, call Sync first.
	 */
	BEAMABLECORE_API void Close(FBeamMappedFile& File);

	BEAMABLECORE_API bool   IsOpen(const FBeamMappedFile& File);
	BEAMABLECORE_API int64  Size  (const FBeamMappedFile& File);

	/**
	 * Optional: force the byte range [Offset, Offset+NumBytes) to disk now.
	 * Translates to FlushViewOfFile on Windows / msync on POSIX.
	 *
	 * You usually don't need to call this — writes through `Data` are already
	 * visible to other processes mapping the same file (OS page cache), and
	 * survive process crashes. Only use Sync when you need power-loss /
	 * kernel-panic durability.
	 */
	BEAMABLECORE_API void Sync(FBeamMappedFile& File, int64 Offset, int64 NumBytes);

	// -------------------------------------------------------------------------
	// Extra header (caller-defined raw bytes between required header and body)
	// -------------------------------------------------------------------------

	/// Pointer to the start of the caller's extra-header region. Length is
	/// reported by `ExtraHeaderSize`. The bytes are zeroed on a fresh open
	/// (`bWasReset == true`); preserved otherwise.
	BEAMABLECORE_API uint8*       ExtraHeader    (FBeamMappedFile& File);
	BEAMABLECORE_API const uint8* ExtraHeader    (const FBeamMappedFile& File);
	BEAMABLECORE_API int32        ExtraHeaderSize(const FBeamMappedFile& File);

	// -------------------------------------------------------------------------
	// Ring buffer
	// -------------------------------------------------------------------------
	// The body region is `[RequiredHeaderSize + ExtraHeaderBytes, Size)`. The
	// utility tracks it internally — you never specify offsets.
	//
	// Slot wire format (within the body):
	//
	//   [u32 PayloadLen] [bytes Payload[PayloadLen]] [u8 Committed]
	//
	// Concurrency:
	//   - Producers (any thread) call RingAppend → CAS-claims a byte range,
	//     writes the slot, release-stores the commit byte. Lock-free.
	//   - The drainer (single thread) calls RingDrain → CAS-resets the head,
	//     walks the prior range, returns committed payloads.

	/// Append `Payload` to the ring. Returns true on success, false on overflow
	/// (no room left between current head and end of body) or if the file is closed.
	BEAMABLECORE_API bool RingAppend(FBeamMappedFile& File, const TArray<uint8>& Payload);

	/// Atomically snapshot all committed slots since last drain, reset head,
	/// and emit each slot's payload into `Out`. Single drainer.
	BEAMABLECORE_API void RingDrain(FBeamMappedFile& File, TArray<TArray<uint8>>& Out);

	/// Read all committed slots WITHOUT resetting the head. Useful for crash
	/// recovery on the next session — pull surviving envelopes out, then call
	/// RingReset to clear the buffer.
	BEAMABLECORE_API void RingReadOnce(const FBeamMappedFile& File, TArray<TArray<uint8>>& Out);

	/// Force-reset the ring: zero the body and reset the head field. The
	/// required header (Magic/Version) and the extra header are left untouched.
	BEAMABLECORE_API void RingReset(FBeamMappedFile& File);

	/// Per-slot overhead: the u32 length prefix + u8 commit byte that wrap each
	/// payload. Use to figure out how much body capacity an N-byte payload needs.
	BEAMABLECORE_API extern const uint32 RingSlotOverhead;

	/// Size of the required header in bytes. Useful when sizing the file:
	/// `Capacity = RequiredHeaderSize + sizeof(YourExtra) + DesiredBodySize`.
	BEAMABLECORE_API extern const int32 RequiredHeaderSize;
}

using FBeamMappedFile = BeamMappedFile::FBeamMappedFile;
