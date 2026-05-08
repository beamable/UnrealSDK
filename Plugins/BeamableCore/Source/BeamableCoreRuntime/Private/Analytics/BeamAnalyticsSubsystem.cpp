#include "Analytics/BeamAnalyticsSubsystem.h"

#include "BeamCoreSettings.h"
#include "BeamInfoData.h"
#include "BeamBackend/BeamBackend.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamMappedFile.h"
#include "UserSlots/BeamUserSlots.h"

#include "Containers/Ticker.h"
#include "Dom/JsonObject.h"
#include "Engine/Engine.h"
#include "HAL/PlatformAtomics.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/DateTime.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UObjectIterator.h"

DEFINE_LOG_CATEGORY_STATIC(LogBeamAnalytics, Log, All);

// =============================================================================
// File layout (top to bottom):
//
//   1. Anonymous namespace utilities — bottom of the stack:
//        a. Analytics file format (magic + extra-header SDK version codec)
//        b. Envelope encode/decode (length-prefixed UTF-8 strings)
//        c. Misc helpers (schema-version probe, SDK-version resolver)
//
//   2. Subsystem methods, in timeline order:
//        a. Lifecycle  — Initialize / Deinitialize
//        b. Tick + Flush — TickFlush / FlushAnalytics / DoFlush
//        c. Network — PostAnalyticsBatch
//        d. Enqueue — EnqueueEventByStruct
//        e. Type-cache + config — RebuildTypeCache / ResolveConfig
//        f. Invalid handling — SetInvalidEventHandler / HandleInvalidEvents
//        g. K2 thunk — K2_EnqueueAnalyticsEvent / execK2_EnqueueAnalyticsEvent
//
// All lock-free ring mechanics live in Serialization/BeamMappedFile.{h,cpp}.
// =============================================================================


namespace
{
	// --------------------------------------------------- 1.a Analytics file format

	constexpr uint32 AnalyticsFileMagic       = 0xBEA50001u;
	constexpr uint32 AnalyticsFileVersion     = 1u;
	constexpr int32  AnalyticsExtraHeaderSize = 64;

	void WriteSdkExtraHeader(FBeamMappedFile& File, const FString& Version)
	{
		uint8*       Extra     = BeamMappedFile::ExtraHeader(File);
		const int32  ExtraSize = BeamMappedFile::ExtraHeaderSize(File);
		if (!Extra || ExtraSize < (int32)sizeof(uint32)) return;

		FMemory::Memzero(Extra, ExtraSize);
		const auto   Utf8       = StringCast<UTF8CHAR>(*Version);
		const uint32 MaxByteLen = static_cast<uint32>(ExtraSize) - (uint32)sizeof(uint32);
		const uint32 Len        = FMath::Min<uint32>(static_cast<uint32>(Utf8.Length()), MaxByteLen);

		FMemory::Memcpy(Extra,                    &Len,       sizeof(uint32));
		FMemory::Memcpy(Extra + sizeof(uint32),   Utf8.Get(), Len);
	}

	FString ReadSdkExtraHeader(const FBeamMappedFile& File)
	{
		const uint8* Extra     = BeamMappedFile::ExtraHeader(File);
		const int32  ExtraSize = BeamMappedFile::ExtraHeaderSize(File);
		if (!Extra || ExtraSize < (int32)sizeof(uint32)) return FString();

		uint32 Len = 0;
		FMemory::Memcpy(&Len, Extra, sizeof(uint32));
		if (Len > (uint32)ExtraSize - sizeof(uint32)) return FString();

		FUTF8ToTCHAR Conv(reinterpret_cast<const ANSICHAR*>(Extra + sizeof(uint32)), static_cast<int32>(Len));
		return FString(Conv.Length(), Conv.Get());
	}


	// --------------------------------------------------- 1.b Envelope codec

	void WriteString(TArray<uint8>& Out, const FString& S)
	{
		const auto Utf8 = StringCast<UTF8CHAR>(*S);
		const uint32 Len = static_cast<uint32>(Utf8.Length());
		const int32 Old = Out.Num();
		Out.SetNumUninitialized(Old + sizeof(uint32) + Len);
		FMemory::Memcpy(Out.GetData() + Old, &Len, sizeof(uint32));
		FMemory::Memcpy(Out.GetData() + Old + sizeof(uint32), Utf8.Get(), Len);
	}

	bool ReadString(const uint8*& Cursor, const uint8* End, FString& Out)
	{
		if (Cursor + sizeof(uint32) > End) return false;
		uint32 Len = 0;
		FMemory::Memcpy(&Len, Cursor, sizeof(uint32));
		Cursor += sizeof(uint32);
		if (Cursor + Len > End) return false;

		FUTF8ToTCHAR Conv(reinterpret_cast<const ANSICHAR*>(Cursor), static_cast<int32>(Len));
		Out = FString(Conv.Length(), Conv.Get());
		Cursor += Len;
		return true;
	}

	void EncodeEnvelope(const FBeamAnalyticsEventEnvelope& Env, TArray<uint8>& Out)
	{
		Out.Reset();
		WriteString(Out, Env.TypeName);
		WriteString(Out, Env.SchemaVersion);
		WriteString(Out, Env.OpCode);
		WriteString(Out, Env.Category);
		WriteString(Out, Env.EventName);
		WriteString(Out, Env.CallsiteJson);
		WriteString(Out, Env.PayloadJson);
		WriteString(Out, Env.UserSlot);
	}

	bool DecodeEnvelope(const TArray<uint8>& Bytes, FBeamAnalyticsEventEnvelope& Out)
	{
		const uint8* Cursor = Bytes.GetData();
		const uint8* End = Cursor + Bytes.Num();
		return ReadString(Cursor, End, Out.TypeName)
		    && ReadString(Cursor, End, Out.SchemaVersion)
		    && ReadString(Cursor, End, Out.OpCode)
		    && ReadString(Cursor, End, Out.Category)
		    && ReadString(Cursor, End, Out.EventName)
		    && ReadString(Cursor, End, Out.CallsiteJson)
		    && ReadString(Cursor, End, Out.PayloadJson)
		    && ReadString(Cursor, End, Out.UserSlot);
	}


	// --------------------------------------------------- 1.c misc helpers

	FString GetSchemaVersionFromCdo(const UScriptStruct* Struct)
	{
		if (!Struct) return TEXT("");
		const FProperty* VersionProp = Struct->FindPropertyByName(TEXT("Version"));
		if (!VersionProp) return TEXT("");

		void* Temp = FMemory::Malloc(Struct->GetStructureSize(), Struct->GetMinAlignment());
		Struct->InitializeStruct(Temp);

		FString Out;
		if (const FStrProperty* SP = CastField<FStrProperty>(VersionProp))
		{
			Out = SP->GetPropertyValue(SP->ContainerPtrToValuePtr<void>(Temp));
		}

		Struct->DestroyStruct(Temp);
		FMemory::Free(Temp);
		return Out;
	}

	FString ResolveSdkVersion()
	{
		const auto* Settings = GetDefault<UBeamCoreSettings>();
		if (Settings && !Settings->BeamableInfoData.IsNull())
		{
			if (UBeamInfoData* Info = Settings->BeamableInfoData.LoadSynchronous())
			{
				return Info->Version.ToString();
			}
		}
		return FString();
	}
}


// =============================================================================
// 2.a Lifecycle
// =============================================================================

void UBeamAnalyticsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UserSlots = GEngine ? GEngine->GetEngineSubsystem<UBeamUserSlots>() : nullptr;

	RebuildTypeCache();

	const auto* Settings = GetDefault<UBeamCoreSettings>();
	for (const FBeamAnalyticsEventConfig& Cfg : Settings->AnalyticsEventConfigs)
	{
		if (Cfg.EventType)
		{
			ConfigCache.Add(Cfg.EventType.Get(), Cfg);
		}
	}

	const FString Path       = FPaths::ProjectSavedDir() / TEXT("BeamAnalytics") / TEXT("events.mmap");
	const int64   Capacity   = Settings->AnalyticsMappedFileSizeBytes;
	const FString SdkVersion = ResolveSdkVersion();

	bool bWasReset = false;
	const bool bOpened = BeamMappedFile::Open(RingFile, Path, Capacity,
		AnalyticsFileMagic, AnalyticsFileVersion,
		AnalyticsExtraHeaderSize, bWasReset);

	if (!bOpened)
	{
		UE_LOG(LogBeamAnalytics, Warning, TEXT("Failed to open analytics ring at %s"), *Path);
	}
	else if (bWasReset)
	{
		WriteSdkExtraHeader(RingFile, SdkVersion);
	}
	else
	{
		const FString OnDiskSdk = ReadSdkExtraHeader(RingFile);
		if (OnDiskSdk != SdkVersion)
		{
			UE_LOG(LogBeamAnalytics, Log,
				TEXT("Analytics ring SDK version drift (on-disk '%s' vs current '%s'); resetting."),
				*OnDiskSdk, *SdkVersion);
			BeamMappedFile::RingReset(RingFile);
			WriteSdkExtraHeader(RingFile, SdkVersion);
		}
		else
		{
			TArray<TArray<uint8>> Recovered;
			BeamMappedFile::RingReadOnce(RingFile, Recovered);

			for (const TArray<uint8>& Bytes : Recovered)
			{
				FBeamAnalyticsEventEnvelope Env;
				if (!DecodeEnvelope(Bytes, Env)) continue;

				UScriptStruct** Found = TypeCacheByName.Find(FName(*Env.TypeName));
				if (!Found || !*Found)
				{
					UE_LOG(LogBeamAnalytics, Warning, TEXT("Recovered envelope of unknown type %s; dropping."), *Env.TypeName);
					continue;
				}
				const FString Current = GetSchemaVersionFromCdo(*Found);
				if (Env.SchemaVersion != Current)
				{
					UE_LOG(LogBeamAnalytics, Warning, TEXT("Recovered envelope of type %s has stale schema %s (current %s); dropping."),
						*Env.TypeName, *Env.SchemaVersion, *Current);
					continue;
				}
				PendingQueue.Enqueue(MoveTemp(Env));
			}

			BeamMappedFile::RingReset(RingFile);
		}
	}

	const float Interval = Settings->AnalyticsFlushIntervalSeconds;
	if (Interval > 0.f)
	{
		TickHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateUObject(this, &UBeamAnalyticsSubsystem::TickFlush), Interval);
	}

#if WITH_EDITOR
	FCoreUObjectDelegates::ReloadCompleteDelegate.AddWeakLambda(this, [this](EReloadCompleteReason)
	{
		RebuildTypeCache();
	});
#endif
}

void UBeamAnalyticsSubsystem::Deinitialize()
{
	if (TickHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
		TickHandle.Reset();
	}

	DoFlush();
	BeamMappedFile::Close(RingFile);

	Super::Deinitialize();
}


// =============================================================================
// 2.b Tick + Flush
// =============================================================================

bool UBeamAnalyticsSubsystem::TickFlush(float /*DeltaTime*/)
{
	DoFlush();
	return true;
}

void UBeamAnalyticsSubsystem::FlushAnalytics()
{
	DoFlush();
}

void UBeamAnalyticsSubsystem::DoFlush()
{
	if (FPlatformAtomics::InterlockedCompareExchange((volatile int8*)&bFlushInFlight, (int8)1, (int8)0) != 0)
	{
		return;
	}
	ON_SCOPE_EXIT
	{
		FPlatformAtomics::InterlockedExchange((volatile int8*)&bFlushInFlight, (int8)0);
	};

	TArray<FBeamAnalyticsEventEnvelope> Envelopes;

	TArray<TArray<uint8>> Drained;
	BeamMappedFile::RingDrain(RingFile, Drained);
	for (const TArray<uint8>& Bytes : Drained)
	{
		FBeamAnalyticsEventEnvelope Env;
		if (DecodeEnvelope(Bytes, Env))
		{
			Envelopes.Add(MoveTemp(Env));
		}
	}

	{
		FBeamAnalyticsEventEnvelope Env;
		while (PendingQueue.Dequeue(Env))
		{
			Envelopes.Add(MoveTemp(Env));
		}
	}

	if (Envelopes.Num() == 0) return;

	TMap<FString, TArray<FBeamAnalyticsEventEnvelope>> ByType;
	for (FBeamAnalyticsEventEnvelope& Env : Envelopes)
	{
		ByType.FindOrAdd(Env.TypeName).Add(MoveTemp(Env));
	}

	for (auto& Pair : ByType)
	{
		const FString& TypeName = Pair.Key;
		TArray<FBeamAnalyticsEventEnvelope>& Group = Pair.Value;

		UScriptStruct** Found = TypeCacheByName.Find(FName(*TypeName));
		if (!Found || !*Found)
		{
			UE_LOG(LogBeamAnalytics, Warning, TEXT("Flush: unknown type %s; dropping %d envelopes."), *TypeName, Group.Num());
			continue;
		}
		UScriptStruct* StructType = *Found;
		const FBeamAnalyticsEventConfig& Cfg = ResolveConfig(StructType);

		TArray<FBeamAnalyticsEventEnvelope> Valid;
		TArray<FBeamAnalyticsEventEnvelope> Invalid;
		Valid.Reserve(Group.Num());

		// One reusable temp instance per type. We Initialize/Destroy around each
		// envelope so generated Validate overrides see a freshly-deserialized event
		// (and so any UPROPERTY heap state from the previous envelope doesn't leak).
		const int32 StructSize  = StructType->GetStructureSize();
		const int32 StructAlign = StructType->GetMinAlignment();
		void* TempMemory = FMemory::Malloc(StructSize, StructAlign);

		for (FBeamAnalyticsEventEnvelope& Env : Group)
		{
			TSharedPtr<FJsonObject> Payload;
			const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Env.PayloadJson);
			const bool bDeserialized = FJsonSerializer::Deserialize(Reader, Payload) && Payload.IsValid();

			bool bValid = false;
			FBeamValidationContext Context;

			if (bDeserialized)
			{
				StructType->InitializeStruct(TempMemory);
				FBeamAnalyticsEvent* Event = static_cast<FBeamAnalyticsEvent*>(TempMemory);
				Event->BeamDeserializeProperties(Payload);
				Event->Validate(Context);
				bValid = Context.IsValid();
				StructType->DestroyStruct(TempMemory);
			}

			if (bValid)
			{
				Valid.Add(MoveTemp(Env));
			}
			else
			{
				if (!bDeserialized)
				{
					UE_LOG(LogBeamAnalytics, Warning, TEXT("Invalid analytics event (%s): payload is not valid JSON."), *Env.TypeName);
				}
				else
				{
					for (const FBeamValidationResult& Fail : Context.FailResults)
					{
						for (const FString& Err : Fail.Errors)
						{
							UE_LOG(LogBeamAnalytics, Verbose, TEXT("Invalid analytics event (%s): [%s] %s"),
								*Env.TypeName, *Fail.PropertyName, *Err);
						}
					}
				}
				Invalid.Add(MoveTemp(Env));
			}
		}

		FMemory::Free(TempMemory);

		if (Invalid.Num() > 0)
		{
			HandleInvalidEvents(StructType, Cfg, Invalid);
		}

		TMap<FString, TArray<TSharedRef<FJsonObject>>> BySlot;

		auto AppendForEnvelopes = [&](const TArray<FBeamAnalyticsEventEnvelope>& List, bool bIsInvalid)
		{
			const bool bEmbedCallsite =
				Cfg.CallsiteInclusion == EBeamAnalyticsCallsiteInclusion::Always
				|| (bIsInvalid && Cfg.CallsiteInclusion == EBeamAnalyticsCallsiteInclusion::OnInvalidOnly);

			for (const FBeamAnalyticsEventEnvelope& Env : List)
			{
				TSharedPtr<FJsonObject> ParamsObj;
				const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Env.PayloadJson);
				if (!FJsonSerializer::Deserialize(Reader, ParamsObj) || !ParamsObj.IsValid())
				{
					ParamsObj = MakeShared<FJsonObject>();
				}

				if (bEmbedCallsite && !Env.CallsiteJson.IsEmpty())
				{
					TSharedPtr<FJsonObject> CallsiteObj;
					const TSharedRef<TJsonReader<>> CR = TJsonReaderFactory<>::Create(Env.CallsiteJson);
					if (FJsonSerializer::Deserialize(CR, CallsiteObj) && CallsiteObj.IsValid())
					{
						ParamsObj->SetObjectField(TEXT("__beamCallsite"), CallsiteObj);
					}
				}

				TSharedPtr<FJsonObject> Top = MakeShared<FJsonObject>();
				Top->SetStringField(TEXT("op"), Env.OpCode.IsEmpty() ? TEXT("g.core") : Env.OpCode);
				Top->SetStringField(TEXT("c"),  Env.Category);
				Top->SetStringField(TEXT("e"),  Env.EventName);
				Top->SetObjectField(TEXT("p"),  ParamsObj);

				BySlot.FindOrAdd(Env.UserSlot).Add(Top.ToSharedRef());
			}
		};

		AppendForEnvelopes(Valid, /*bIsInvalid=*/false);

		if (Cfg.InvalidBehavior == EBeamInvalidEventBehavior::SendAsIs ||
		    Cfg.InvalidBehavior == EBeamInvalidEventBehavior::LogOnly)
		{
			AppendForEnvelopes(Invalid, /*bIsInvalid=*/true);
		}

		for (auto& SlotPair : BySlot)
		{
			FUserSlot Slot = SlotPair.Key.IsEmpty()
				? GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot()
				: FUserSlot(SlotPair.Key);
			PostAnalyticsBatch(Slot, SlotPair.Value);
		}
	}
}


// =============================================================================
// 2.c Network
// =============================================================================

void UBeamAnalyticsSubsystem::PostAnalyticsBatch(const FUserSlot& Slot, const TArray<TSharedRef<FJsonObject>>& Events)
{
	if (Events.Num() == 0) return;
	if (!UserSlots) return;

	FBeamRealmUser UserData;
	if (!UserSlots->GetUserDataAtSlot(Slot, UserData, this))
	{
		UE_LOG(LogBeamAnalytics, Warning, TEXT("No user data for slot '%s'; skipping %d events."), *Slot.Name, Events.Num());
		return;
	}

	const auto* Settings = GetDefault<UBeamCoreSettings>();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = FHttpModule::Get().CreateRequest();
	
	const FString AuthHeader = FString::Format(*UBeamBackend::HEADER_VALUE_AUTHORIZATION, {UserData.AuthToken.AccessToken});
	Req->SetHeader(UBeamBackend::HEADER_AUTHORIZATION, AuthHeader);
		Req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	const FString Url = FString::Format(
		TEXT("https://{0}/report/custom_batch/{1}/{2}/{3}"),
		{Settings->BeamableEnvironment->APIUrl, Settings->TargetRealm.Cid.AsString, Settings->TargetRealm.Pid.AsString, UserData.GamerTag.AsString});
	Req->SetURL(Url);
	Req->SetVerb(TEXT("POST"));

	TArray<FString> EventJsons;
	EventJsons.Reserve(Events.Num());
	for (const TSharedRef<FJsonObject>& Top : Events)
	{
		FString Out;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
		if (FJsonSerializer::Serialize(Top, Writer))
		{
			EventJsons.Add(Out);
		}
	}
	if (EventJsons.Num() == 0) return;

	const FString Body = TEXT("[") + FString::Join(EventJsons, TEXT(", ")) + TEXT("]");
	FTCHARToUTF8 Converter(*Body);
	TArray<uint8> Content;
	Content.Append(reinterpret_cast<const uint8*>(Converter.Get()), Converter.Length());
	Req->SetContent(Content);

	const int32 Count = EventJsons.Num();
	Req->OnProcessRequestComplete().BindLambda([Count](FHttpRequestPtr, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			UE_LOG(LogBeamAnalytics, Verbose, TEXT("Analytics batch (%d events) sent."), Count);
		}
		else
		{
			UE_LOG(LogBeamAnalytics, Warning, TEXT("Analytics batch (%d events) failed."), Count);
		}
	});
	Req->ProcessRequest();
}


// =============================================================================
// 2.d Enqueue
// =============================================================================

bool UBeamAnalyticsSubsystem::EnqueueEventByStruct(const UScriptStruct* StructType, const void* StructData,
	const FBeamAnalyticsCallsite& Callsite, const FUserSlot& Slot)
{
	if (!StructType || !StructData) return false;
	if (!StructType->IsChildOf(FBeamAnalyticsEvent::StaticStruct())) return false;

	const FBeamAnalyticsEventConfig& Cfg = ResolveConfig(StructType);

	if (Cfg.SampleRate < 1.f)
	{
		if (Cfg.SampleRate <= 0.f) return true;
		if (FMath::FRand() >= Cfg.SampleRate) return true;
	}

	const FBeamAnalyticsEvent* AsEvent = static_cast<const FBeamAnalyticsEvent*>(StructData);

	FString PayloadJson;
	AsEvent->BuildParamsJsonString(PayloadJson);

	FString CallsiteJson;
	{
		FBeamAnalyticsCallsite Copy = Callsite;
		if (Copy.TimestampUtcSeconds == 0.0)
		{
			Copy.TimestampUtcSeconds = FDateTime::UtcNow().ToUnixTimestampDecimal();
		}
		if (Copy.UserSlot.IsEmpty())
		{
			Copy.UserSlot = Slot.Name;
		}
		TUnrealJsonSerializer Writer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&CallsiteJson);
		Copy.BeamSerialize(Writer);
		Writer->Close();
	}

	FBeamAnalyticsEventEnvelope Env;
	Env.TypeName      = StructType->GetPathName();
	Env.SchemaVersion = AsEvent->Version;
	Env.OpCode        = AsEvent->GetOpCode();
	Env.Category      = AsEvent->GetCategory();
	Env.EventName     = AsEvent->GetEventName();
	Env.CallsiteJson  = CallsiteJson;
	Env.PayloadJson   = PayloadJson;
	Env.UserSlot      = Slot.Name;

	TArray<uint8> Bytes;
	EncodeEnvelope(Env, Bytes);

	if (BeamMappedFile::RingAppend(RingFile, Bytes))
	{
		return true;
	}

	PendingQueue.Enqueue(MoveTemp(Env));
	return false;
}


// =============================================================================
// 2.e Type cache + config
// =============================================================================

void UBeamAnalyticsSubsystem::RebuildTypeCache()
{
	TypeCacheByName.Reset();
	KnownEventTypes.Reset();

	UScriptStruct* Base = FBeamAnalyticsEvent::StaticStruct();
	for (TObjectIterator<UScriptStruct> It; It; ++It)
	{
		UScriptStruct* S = *It;
		if (!S || S == Base) continue;
		if (S->IsChildOf(Base))
		{
			KnownEventTypes.Add(S);
			TypeCacheByName.Add(FName(*S->GetPathName()), S);
		}
	}
}

const FBeamAnalyticsEventConfig& UBeamAnalyticsSubsystem::ResolveConfig(const UScriptStruct* StructType) const
{
	if (StructType)
	{
		if (const FBeamAnalyticsEventConfig* Found = ConfigCache.Find(StructType))
		{
			return *Found;
		}
	}
	return GetDefault<UBeamCoreSettings>()->AnalyticsFallbackConfig;
}


// =============================================================================
// 2.f Invalid handling
// =============================================================================

void UBeamAnalyticsSubsystem::SetInvalidEventHandler(const UScriptStruct* StructType, FBeamInvalidEventHandler Handler)
{
	if (!StructType) return;
	if (Handler.IsBound())
	{
		InvalidHandlers.Add(StructType, Handler);
	}
	else
	{
		InvalidHandlers.Remove(StructType);
	}
}

void UBeamAnalyticsSubsystem::HandleInvalidEvents(const UScriptStruct* StructType,
	const FBeamAnalyticsEventConfig& Config, TArray<FBeamAnalyticsEventEnvelope>& Invalid)
{
	switch (Config.InvalidBehavior)
	{
	case EBeamInvalidEventBehavior::Drop:
		Invalid.Reset();
		return;

	case EBeamInvalidEventBehavior::LogOnly:
		for (const FBeamAnalyticsEventEnvelope& Env : Invalid)
		{
			UE_LOG(LogBeamAnalytics, Warning, TEXT("Invalid analytics event (%s): %s"), *Env.TypeName, *Env.PayloadJson);
		}
		return;

	case EBeamInvalidEventBehavior::SendAsIs:
		return;

	case EBeamInvalidEventBehavior::EnsureOrCheck:
		for (const FBeamAnalyticsEventEnvelope& Env : Invalid)
		{
			if (Config.bUseEnsureNotCheck)
			{
				ensureMsgf(false, TEXT("Invalid analytics event (%s): %s"), *Env.TypeName, *Env.PayloadJson);
			}
			else
			{
				checkf(false, TEXT("Invalid analytics event (%s): %s"), *Env.TypeName, *Env.PayloadJson);
			}
		}
		return;

	case EBeamInvalidEventBehavior::Custom:
		if (FBeamInvalidEventHandler* Handler = InvalidHandlers.Find(StructType))
		{
			if (Handler->IsBound())
			{
				Handler->Execute(StructType, Invalid);
				return;
			}
		}
		UE_LOG(LogBeamAnalytics, Warning, TEXT("EBeamInvalidEventBehavior::Custom for %s but no handler registered; dropping."), *StructType->GetName());
		Invalid.Reset();
		return;
	}
}


// =============================================================================
// 2.g K2 thunk
// =============================================================================

bool UBeamAnalyticsSubsystem::K2_EnqueueAnalyticsEvent(FUserSlot /*Slot*/,
	const FString& /*BlueprintCallsiteFile*/, int32 /*BlueprintCallsiteLine*/, const FString& /*BlueprintCallsiteFunction*/,
	const int32& /*EventStruct*/)
{
	checkNoEntry();
	return false;
}

DEFINE_FUNCTION(UBeamAnalyticsSubsystem::execK2_EnqueueAnalyticsEvent)
{
	FUserSlot Slot;
	Stack.StepCompiledIn<FStructProperty>(&Slot);

	FString CallsiteFile;
	Stack.StepCompiledIn<FStrProperty>(&CallsiteFile);

	int32 CallsiteLine = 0;
	Stack.StepCompiledIn<FIntProperty>(&CallsiteLine);

	FString CallsiteFunction;
	Stack.StepCompiledIn<FStrProperty>(&CallsiteFunction);

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentProperty        = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);
	void* StructAddr = Stack.MostRecentPropertyAddress;
	const FStructProperty* StructProp = CastField<FStructProperty>(Stack.MostRecentProperty);

	P_FINISH;

	bool bResult = false;
	if (P_THIS && StructProp && StructProp->Struct && StructAddr)
	{
		FBeamAnalyticsCallsite Callsite(CallsiteFile, CallsiteLine, CallsiteFunction,
			FDateTime::UtcNow().ToUnixTimestampDecimal(), FString());

		P_NATIVE_BEGIN;
		bResult = P_THIS->EnqueueEventByStruct(StructProp->Struct, StructAddr, Callsite, Slot);
		P_NATIVE_END;
	}
	*static_cast<bool*>(RESULT_PARAM) = bResult;
}
