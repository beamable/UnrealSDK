#include "Serialization/BeamMappedFile.h"

#include "HAL/PlatformFileManager.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "HAL/PlatformAtomics.h"
#include "Misc/AutomationTest.h"
#include "Misc/Paths.h"

namespace
{
	// Caller-defined "extra header" used by most tests — sits right after the
	// utility's required header. The size of this struct (or any size you like)
	// gets passed to Open(). All-binary on purpose: no null-terminated strings
	// in on-disk data.
	struct FTestExtraHeader
	{
		uint32 SchemaVersion;
		uint32 Marker;
	};
	static_assert(sizeof(FTestExtraHeader) == 8);

	constexpr uint32 kTestMagic   = 0xABBA1234u;
	constexpr uint32 kTestVersion = 1u;

	FString TempPath(const TCHAR* Suffix)
	{
		return FPaths::ProjectIntermediateDir() / TEXT("BeamMappedFileTests") / FString::Printf(TEXT("test_%s.bin"), Suffix);
	}

	void DeleteIfExists(const FString& Path)
	{
		IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
		if (PF.FileExists(*Path)) PF.DeleteFile(*Path);
	}

	TArray<uint8> MakePayload(uint8 Fill, int32 Size)
	{
		TArray<uint8> Out;
		Out.SetNumUninitialized(Size);
		FMemory::Memset(Out.GetData(), Fill, Size);
		return Out;
	}
}

BEGIN_DEFINE_SPEC(FBeamMappedFileSpec, "BeamableUnreal.BeamMappedFile",
	EAutomationTestFlags::ProductFilter | EAutomationTestFlags::EditorContext)
END_DEFINE_SPEC(FBeamMappedFileSpec)

void FBeamMappedFileSpec::Define()
{
	using namespace BeamMappedFile;

	// =========================================================================
	// Lifecycle
	// =========================================================================
	Describe("Lifecycle", [this]()
	{
		It("creates a new file at the requested capacity and reports IsOpen", [this]()
		{
			const FString Path = TempPath(TEXT("create"));
			DeleteIfExists(Path);

			FBeamMappedFile File;
			bool bWasReset = false;
			TestTrue ("Open succeeds",       Open(File, Path, 4096, kTestMagic, kTestVersion, sizeof(FTestExtraHeader), bWasReset));
			TestTrue ("Was reset (new file)", bWasReset);
			TestTrue ("IsOpen",               IsOpen(File));
			TestEqual("Size matches",         Size(File), (int64)4096);
			TestTrue ("File on disk",         FPlatformFileManager::Get().GetPlatformFile().FileExists(*Path));

			Close(File);
			TestFalse("Closed not open", IsOpen(File));
			TestEqual("Closed size==0",  Size(File), (int64)0);

			DeleteIfExists(Path);
		});

		It("Close is idempotent", [this]()
		{
			FBeamMappedFile File;
			Close(File); // No-op on default-constructed.
			Close(File);
			TestFalse("Still closed", IsOpen(File));
		});

		It("rejects non-positive capacity", [this]()
		{
			// Open intentionally logs an error here; declare it expected so the
			// automation framework doesn't fail the test on the log line.
			AddExpectedError(TEXT("non-positive capacity"), EAutomationExpectedErrorFlags::Contains, 1);

			FBeamMappedFile File;
			bool bWasReset = false;
			TestFalse("Capacity 0 fails", Open(File, TempPath(TEXT("zero")), 0, kTestMagic, kTestVersion, 0, bWasReset));
			TestFalse("IsOpen",           IsOpen(File));
		});

		It("rejects negative ExtraHeaderBytes", [this]()
		{
			AddExpectedError(TEXT("negative ExtraHeaderBytes"), EAutomationExpectedErrorFlags::Contains, 1);

			FBeamMappedFile File;
			bool bWasReset = false;
			TestFalse("Negative extra fails", Open(File, TempPath(TEXT("neg_extra")), 4096, kTestMagic, kTestVersion, -1, bWasReset));
		});
	});

	// =========================================================================
	// Required header validation
	// =========================================================================
	Describe("Required header", [this]()
	{
		It("preserves contents when reopened with same Magic+Version", [this]()
		{
			const FString Path = TempPath(TEXT("preserve_match"));
			DeleteIfExists(Path);

			// Session 1: write a marker into the body.
			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, kTestMagic, kTestVersion, sizeof(FTestExtraHeader), bWasReset);
				TestTrue("Was reset (new file)", bWasReset);

				// Stamp a byte in the body region so we can detect preservation.
				const int64 BodyStart = RequiredHeaderSize + sizeof(FTestExtraHeader);
				File.Data[BodyStart + 100] = 0x42;
				Close(File);
			}

			// Session 2: same Magic+Version → should NOT reset; marker survives.
			{
				FBeamMappedFile File;
				bool bWasReset = true;
				Open(File, Path, 4096, kTestMagic, kTestVersion, sizeof(FTestExtraHeader), bWasReset);
				TestFalse("Was NOT reset",     bWasReset);

				const int64 BodyStart = RequiredHeaderSize + sizeof(FTestExtraHeader);
				TestEqual ("Marker preserved", File.Data[BodyStart + 100], (uint8)0x42);
				Close(File);
			}

			DeleteIfExists(Path);
		});

		It("resets when Magic differs", [this]()
		{
			const FString Path = TempPath(TEXT("reset_magic"));
			DeleteIfExists(Path);

			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, kTestMagic, kTestVersion, 0, bWasReset);
				const int64 BodyStart = RequiredHeaderSize;
				File.Data[BodyStart + 50] = 0x77;
				Close(File);
			}

			{
				FBeamMappedFile File;
				bool bWasReset = false;
				const uint32 OtherMagic = 0xDEADBEEFu;
				Open(File, Path, 4096, OtherMagic, kTestVersion, 0, bWasReset);
				TestTrue ("Was reset (magic mismatch)", bWasReset);

				const int64 BodyStart = RequiredHeaderSize;
				TestEqual("Marker zeroed",              File.Data[BodyStart + 50], (uint8)0);
				Close(File);
			}

			DeleteIfExists(Path);
		});

		It("resets when Version differs", [this]()
		{
			const FString Path = TempPath(TEXT("reset_version"));
			DeleteIfExists(Path);

			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, kTestMagic, kTestVersion, 0, bWasReset);
				const int64 BodyStart = RequiredHeaderSize;
				File.Data[BodyStart + 50] = 0x77;
				Close(File);
			}

			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, kTestMagic, /*OtherVersion=*/99, 0, bWasReset);
				TestTrue ("Was reset (version mismatch)", bWasReset);

				const int64 BodyStart = RequiredHeaderSize;
				TestEqual("Marker zeroed",                File.Data[BodyStart + 50], (uint8)0);
				Close(File);
			}

			DeleteIfExists(Path);
		});
	});

	// =========================================================================
	// Extra header
	// =========================================================================
	Describe("Extra header", [this]()
	{
		It("round-trips an extra header struct", [this]()
		{
			const FString Path = TempPath(TEXT("extra_rt"));
			DeleteIfExists(Path);

			FBeamMappedFile File;
			bool bWasReset = false;
			Open(File, Path, 4096, kTestMagic, kTestVersion, sizeof(FTestExtraHeader), bWasReset);

			TestEqual("ExtraHeaderSize matches", ExtraHeaderSize(File), (int32)sizeof(FTestExtraHeader));
			TestNotNull("ExtraHeader pointer",    ExtraHeader(File));

			const FTestExtraHeader Written{ /*SchemaVersion=*/ 7u, /*Marker=*/ 0xCAFEBABEu };
			FMemory::Memcpy(ExtraHeader(File), &Written, sizeof(Written));

			FTestExtraHeader ReadBack = {};
			FMemory::Memcpy(&ReadBack, ExtraHeader(File), sizeof(ReadBack));
			TestEqual("SchemaVersion", ReadBack.SchemaVersion, (uint32)7);
			TestEqual("Marker",        ReadBack.Marker,        (uint32)0xCAFEBABEu);

			Close(File);
			DeleteIfExists(Path);
		});

		It("persists the extra header across reopen", [this]()
		{
			const FString Path = TempPath(TEXT("extra_persist"));
			DeleteIfExists(Path);

			const FTestExtraHeader Written{ /*SchemaVersion=*/ 42u, /*Marker=*/ 0xDEADBEEFu };

			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, kTestMagic, kTestVersion, sizeof(FTestExtraHeader), bWasReset);
				FMemory::Memcpy(ExtraHeader(File), &Written, sizeof(Written));
				Close(File);
			}

			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, kTestMagic, kTestVersion, sizeof(FTestExtraHeader), bWasReset);
				TestFalse("Was NOT reset", bWasReset);

				FTestExtraHeader OnDisk = {};
				FMemory::Memcpy(&OnDisk, ExtraHeader(File), sizeof(OnDisk));
				TestEqual("SchemaVersion preserved", OnDisk.SchemaVersion, (uint32)42);
				TestEqual("Marker preserved",        OnDisk.Marker,        (uint32)0xDEADBEEFu);
				Close(File);
			}

			DeleteIfExists(Path);
		});

		It("is zeroed when the required header validation fails", [this]()
		{
			const FString Path = TempPath(TEXT("extra_zeroed"));
			DeleteIfExists(Path);

			// Session 1: stamp extra header.
			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, kTestMagic, kTestVersion, sizeof(FTestExtraHeader), bWasReset);
				FTestExtraHeader Extra = {};
				Extra.SchemaVersion = 99;
				FMemory::Memcpy(ExtraHeader(File), &Extra, sizeof(Extra));
				Close(File);
			}

			// Session 2: incompatible Magic → entire mapping wiped, including extra header.
			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, /*OtherMagic=*/0xCAFEBABEu, kTestVersion, sizeof(FTestExtraHeader), bWasReset);
				TestTrue("Was reset", bWasReset);

				FTestExtraHeader Extra = {};
				FMemory::Memcpy(&Extra, ExtraHeader(File), sizeof(Extra));
				TestEqual("Extra header zeroed", Extra.SchemaVersion, (uint32)0);
				Close(File);
			}

			DeleteIfExists(Path);
		});
	});

	// =========================================================================
	// Ring buffer
	// =========================================================================
	Describe("Ring buffer", [this]()
	{
		It("appends a single payload and drains it back", [this]()
		{
			const FString Path = TempPath(TEXT("ring_one"));
			DeleteIfExists(Path);

			FBeamMappedFile File;
			bool bWasReset = false;
			Open(File, Path, 4096, kTestMagic, kTestVersion, /*ExtraHeaderBytes=*/0, bWasReset);

			TArray<uint8> Payload = MakePayload(0xAB, 32);
			TestTrue("Append OK", RingAppend(File, Payload));

			TArray<TArray<uint8>> Drained;
			RingDrain(File, Drained);
			TestEqual ("Drained 1",      Drained.Num(),     1);
			TestEqual ("Payload size",   Drained[0].Num(),  32);
			TestEqual ("Payload bytes",  Drained[0][0],     (uint8)0xAB);

			Close(File);
			DeleteIfExists(Path);
		});

		It("appends many payloads and drains them all in order", [this]()
		{
			const FString Path = TempPath(TEXT("ring_many"));
			DeleteIfExists(Path);

			FBeamMappedFile File;
			bool bWasReset = false;
			Open(File, Path, 64 * 1024, kTestMagic, kTestVersion, 0, bWasReset);

			constexpr int32 N = 100;
			for (int32 i = 0; i < N; ++i)
			{
				TArray<uint8> P = MakePayload((uint8)(i & 0xFF), 16);
				TestTrue(FString::Printf(TEXT("Append #%d"), i), RingAppend(File, P));
			}

			TArray<TArray<uint8>> Drained;
			RingDrain(File, Drained);
			TestEqual("Drained count", Drained.Num(), N);
			for (int32 i = 0; i < N; ++i)
			{
				TestEqual(FString::Printf(TEXT("Payload[%d] first byte"), i),
					Drained[i][0], (uint8)(i & 0xFF));
			}

			Close(File);
			DeleteIfExists(Path);
		});

		It("returns false on overflow", [this]()
		{
			const FString Path = TempPath(TEXT("ring_overflow"));
			DeleteIfExists(Path);

			// Tiny capacity: only a couple of small slots fit (after the 16-byte
			// required header + 0 extra). Each append is 16-byte payload + 5-byte
			// overhead = 21 bytes. Body = 64 bytes → 3 slots fit (63 bytes).
			FBeamMappedFile File;
			bool bWasReset = false;
			Open(File, Path, RequiredHeaderSize + 64, kTestMagic, kTestVersion, 0, bWasReset);

			TestTrue ("1st", RingAppend(File, MakePayload(1, 16)));
			TestTrue ("2nd", RingAppend(File, MakePayload(2, 16)));
			TestTrue ("3rd", RingAppend(File, MakePayload(3, 16)));
			TestFalse("4th overflows", RingAppend(File, MakePayload(4, 16)));

			TArray<TArray<uint8>> Out;
			RingDrain(File, Out);
			TestEqual("Drained 3", Out.Num(), 3);
			TestTrue ("Append after drain", RingAppend(File, MakePayload(5, 16)));

			Close(File);
			DeleteIfExists(Path);
		});

		It("RingReadOnce recovers committed slots without resetting head", [this]()
		{
			const FString Path = TempPath(TEXT("ring_recover"));
			DeleteIfExists(Path);

			// Session 1: write three slots and exit without draining.
			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, kTestMagic, kTestVersion, 0, bWasReset);
				RingAppend(File, MakePayload(11, 8));
				RingAppend(File, MakePayload(22, 8));
				RingAppend(File, MakePayload(33, 8));
				Close(File);
			}

			// Session 2: open with same Magic+Version, RingReadOnce, expect three.
			{
				FBeamMappedFile File;
				bool bWasReset = false;
				Open(File, Path, 4096, kTestMagic, kTestVersion, 0, bWasReset);
				TestFalse("Was NOT reset", bWasReset);

				TArray<TArray<uint8>> Out;
				RingReadOnce(File, Out);
				TestEqual("Recovered 3",    Out.Num(),       3);
				TestEqual("Slot 0 marker", Out[0][0], (uint8)11);
				TestEqual("Slot 1 marker", Out[1][0], (uint8)22);
				TestEqual("Slot 2 marker", Out[2][0], (uint8)33);

				// RingReset clears the body.
				RingReset(File);
				TArray<TArray<uint8>> AfterReset;
				RingReadOnce(File, AfterReset);
				TestEqual("Empty after reset", AfterReset.Num(), 0);

				Close(File);
			}

			DeleteIfExists(Path);
		});

		It("survives zero-length payloads", [this]()
		{
			const FString Path = TempPath(TEXT("ring_zero"));
			DeleteIfExists(Path);

			FBeamMappedFile File;
			bool bWasReset = false;
			Open(File, Path, 4096, kTestMagic, kTestVersion, 0, bWasReset);

			TestTrue("Append empty", RingAppend(File, TArray<uint8>{}));

			TArray<TArray<uint8>> Out;
			RingDrain(File, Out);
			TestEqual("Drained 1", Out.Num(),    1);
			TestEqual("Empty",     Out[0].Num(), 0);

			Close(File);
			DeleteIfExists(Path);
		});

		// -------------------------------------------------------------------
		// Concurrency: multiple producers, one drainer.
		// -------------------------------------------------------------------
		It("is correct under concurrent producers (lock-free CAS)", [this]()
		{
			const FString Path = TempPath(TEXT("ring_concurrent"));
			DeleteIfExists(Path);

			FBeamMappedFile File;
			bool bWasReset = false;
			Open(File, Path, 1 * 1024 * 1024, kTestMagic, kTestVersion, 0, bWasReset);

			constexpr int32 NumThreads  = 8;
			constexpr int32 PerThread   = 250;
			constexpr int32 PayloadSize = 32;

			class FProducer : public FRunnable
			{
			public:
				FBeamMappedFile* File;
				uint8 ThreadId;
				int32 Count;
				int32 PayloadSize;
				TAtomic<int32> Succeeded{0};

				virtual uint32 Run() override
				{
					for (int32 i = 0; i < Count; ++i)
					{
						TArray<uint8> P;
						P.SetNumUninitialized(PayloadSize);
						FMemory::Memset(P.GetData(), ThreadId, PayloadSize);
						if (RingAppend(*File, P))
						{
							Succeeded.IncrementExchange();
						}
					}
					return 0;
				}
			};

			TArray<TUniquePtr<FProducer>>       Producers;
			TArray<TUniquePtr<FRunnableThread>> Threads;
			Producers.Reserve(NumThreads);
			Threads.Reserve(NumThreads);

			for (int32 t = 0; t < NumThreads; ++t)
			{
				auto P = MakeUnique<FProducer>();
				P->File        = &File;
				P->ThreadId    = (uint8)(0x10 + t);
				P->Count       = PerThread;
				P->PayloadSize = PayloadSize;

				Threads.Add(TUniquePtr<FRunnableThread>(FRunnableThread::Create(P.Get(), *FString::Printf(TEXT("BeamMappedFileSpec_%d"), t))));
				Producers.Add(MoveTemp(P));
			}

			for (auto& T : Threads) { T->WaitForCompletion(); }

			int32 TotalSucceeded = 0;
			for (auto& P : Producers) { TotalSucceeded += P->Succeeded.Load(); }
			TestEqual("All appends fit", TotalSucceeded, NumThreads * PerThread);

			TArray<TArray<uint8>> Drained;
			RingDrain(File, Drained);
			TestEqual("Drained == produced", Drained.Num(), TotalSucceeded);

			TMap<uint8, int32> CountByTag;
			for (const TArray<uint8>& P : Drained)
			{
				if (P.Num() != PayloadSize) continue;
				const uint8 Tag = P[0];
				bool bAllSame = true;
				for (uint8 B : P) { if (B != Tag) { bAllSame = false; break; } }
				if (bAllSame) CountByTag.FindOrAdd(Tag)++;
			}

			for (int32 t = 0; t < NumThreads; ++t)
			{
				const uint8 Tag = (uint8)(0x10 + t);
				TestEqual(FString::Printf(TEXT("Thread %d count"), t),
					CountByTag.FindRef(Tag), PerThread);
			}

			Close(File);
			DeleteIfExists(Path);
		});
	});
}
