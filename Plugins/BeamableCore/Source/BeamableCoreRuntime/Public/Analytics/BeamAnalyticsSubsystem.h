#pragma once

// =============================================================================
// UBeamAnalyticsSubsystem — typed analytics pipeline (UBeamRuntimeSubsystem)
// -----------------------------------------------------------------------------
// What this subsystem does, end to end:
//
//   1. Game/editor code constructs a USTRUCT deriving from FBeamAnalyticsEvent
//      and calls EnqueueEvent (or BEAM_ENQUEUE_ANALYTICS_EVENT for callsite tagging).
//   2. The subsystem captures the wire-format identifiers (op/category/event-name)
//      from the event's virtual methods, serializes the params to JSON, and writes
//      the result via BeamMappedFile to a memory-mapped ring buffer.
//   3. Either every UBeamCoreSettings::AnalyticsFlushIntervalSeconds tick, or on
//      explicit FlushAnalytics, the subsystem drains the ring + the in-memory
//      overflow queue, validates per type, and POSTs a batch to
//      api.beamable.com/report/custom_batch/{cid}/{pid}/{gamer_tag}.
//   4. Invalid events are dropped / logged / sent as-is / asserted / dispatched
//      to a registered C++ handler depending on the per-type config.
//
// Lives in BeamableCoreRuntime as a UBeamRuntimeSubsystem so it can hook into
// the Beamable runtime lifecycle (OnBeamableStarting / OnUserSignedIn / etc.)
// when those become useful, and so its lifetime is naturally scoped to the
// owning UGameInstance.
// =============================================================================

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "UObject/ScriptInterface.h"
#include "Containers/Queue.h"
#include "Containers/Ticker.h"

#include "Analytics/BeamAnalyticsEvent.h"
#include "Serialization/BeamMappedFile.h"
#include "UserSlots/UserSlot.h"

#include "BeamAnalyticsSubsystem.generated.h"

class UBeamUserSlots;
struct FBeamRealmUser;

/**
 * Custom invalid-event handler delegate. Registered per UScriptStruct via
 * SetInvalidEventHandler. Invoked by HandleInvalidEvents when the per-type
 * config sets InvalidBehavior = Custom.
 */
DECLARE_DELEGATE_TwoParams(FBeamInvalidEventHandler,
                           const UScriptStruct* /*Type*/,
                           TArray<FBeamAnalyticsEventEnvelope>& /*Invalid*/);


// -----------------------------------------------------------------------------
// FBeamAnalyticsLegacyEvent
// -----------------------------------------------------------------------------
/**
 * Backwards-compatibility carrier for the four deprecated UBeamRuntime::
 * SendAnalyticsEvent* methods. Holds the per-call op/category/event-name and
 * the user-provided params JSON string, and overrides the FBeamAnalyticsEvent
 * virtuals so the resulting batch wire format is byte-identical to what the
 * old UBeamRuntime path emitted.
 */
USTRUCT()
struct BEAMABLECORERUNTIME_API FBeamAnalyticsLegacyEvent : public FBeamAnalyticsEvent
{
	GENERATED_BODY()

	UPROPERTY() FString Category;
	UPROPERTY() FString EventName;
	UPROPERTY() FString OpCode = TEXT("g.core");
	UPROPERTY() FString ParamsJson;

	virtual FString GetOpCode()    const override { return OpCode; }
	virtual FString GetCategory()  const override { return Category; }
	virtual FString GetEventName() const override { return EventName; }
	virtual void    BuildParamsJsonString(FString& Out) const override { Out = ParamsJson; }
};


// -----------------------------------------------------------------------------
// UBeamAnalyticsSubsystem
// -----------------------------------------------------------------------------
/**
 * UBeamRuntimeSubsystem that owns the analytics pipeline (storage, batching,
 * validation, network send). Per-UGameInstance lifetime.
 *
 * Members below are organized in timeline order:
 *
 *   1. Lifecycle           — Initialize / Deinitialize / GetSelf
 *   2. Flush (public)      — FlushAnalytics
 *   3. Enqueue (public)    — EnqueueEvent / EnqueueEventForSlot / EnqueueEventByStruct
 *   4. Extensibility       — SetInvalidEventHandler / RebuildTypeCache / GetKnownEventTypes
 *   5. Blueprint thunk     — K2_EnqueueAnalyticsEvent (called only by the K2 send-event node)
 *   6. Private flush path  — TickFlush / DoFlush / PostAnalyticsBatch
 *   7. Private utilities   — ResolveConfig / HandleInvalidEvents
 *   8. State
 */
UCLASS(NotBlueprintable)
class BEAMABLECORERUNTIME_API UBeamAnalyticsSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

public:
	// ------------------------------------------------------------- 1. Lifecycle

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 * Resolve the subsystem instance via the calling object's UWorld→UGameInstance.
	 * Used by the K2 send-event node's expansion and by C++ callers that want a
	 * one-liner.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Analytics",
		meta=(BlueprintInternalUseOnly="true", WorldContext="CallingContext"))
	static UBeamAnalyticsSubsystem* GetSelf(const UObject* CallingContext)
	{
		if (!CallingContext) return nullptr;
		if (UWorld* World = CallingContext->GetWorld())
		{
			if (UGameInstance* GI = World->GetGameInstance())
			{
				return GI->GetSubsystem<UBeamAnalyticsSubsystem>();
			}
		}
		return nullptr;
	}

	// --------------------------------------------------------------- 2. Flush

	/** Force a flush right now: drains the ring + in-memory queue and dispatches HTTP POSTs. */
	UFUNCTION(BlueprintCallable, Category="Beam|Analytics")
	void FlushAnalytics();

	// ------------------------------------------------------------- 3. Enqueue

	/** Enqueue a typed analytics event (no callsite). Prefer BEAM_ENQUEUE_ANALYTICS_EVENT for callsite tagging. */
	template <typename TEvent>
	bool EnqueueEvent(const TEvent& Event)
	{
		static_assert(TIsDerivedFrom<TEvent, FBeamAnalyticsEvent>::Value, "TEvent must derive from FBeamAnalyticsEvent");
		return EnqueueEventByStruct(TEvent::StaticStruct(), &Event, FBeamAnalyticsCallsite{}, FUserSlot{});
	}

	template <typename TEvent>
	bool EnqueueEvent(const TEvent& Event, const FBeamAnalyticsCallsite& Callsite)
	{
		static_assert(TIsDerivedFrom<TEvent, FBeamAnalyticsEvent>::Value, "TEvent must derive from FBeamAnalyticsEvent");
		return EnqueueEventByStruct(TEvent::StaticStruct(), &Event, Callsite, FUserSlot{});
	}

	template <typename TEvent>
	bool EnqueueEventForSlot(const FUserSlot& Slot, const TEvent& Event)
	{
		static_assert(TIsDerivedFrom<TEvent, FBeamAnalyticsEvent>::Value, "TEvent must derive from FBeamAnalyticsEvent");
		return EnqueueEventByStruct(TEvent::StaticStruct(), &Event, FBeamAnalyticsCallsite{}, Slot);
	}

	template <typename TEvent>
	bool EnqueueEventForSlot(const FUserSlot& Slot, const TEvent& Event, const FBeamAnalyticsCallsite& Callsite)
	{
		static_assert(TIsDerivedFrom<TEvent, FBeamAnalyticsEvent>::Value, "TEvent must derive from FBeamAnalyticsEvent");
		return EnqueueEventByStruct(TEvent::StaticStruct(), &Event, Callsite, Slot);
	}

	/** Untyped enqueue path. StructType MUST derive from FBeamAnalyticsEvent. */
	bool EnqueueEventByStruct(const UScriptStruct* StructType, const void* StructData,
	                          const FBeamAnalyticsCallsite& Callsite, const FUserSlot& Slot);

	// --------------------------------------------------------- 4. Extensibility

	void SetInvalidEventHandler(const UScriptStruct* StructType, FBeamInvalidEventHandler Handler);

	void RebuildTypeCache();

	const TArray<UScriptStruct*>& GetKnownEventTypes() const { return KnownEventTypes; }

	// --------------------------------------------------------- 5. Blueprint thunk

	/**
	 * Custom-thunk hook for the K2 send-event node. Reads the wildcard struct
	 * off the script stack and forwards to EnqueueEventByStruct. Not callable
	 * directly from Blueprints — the K2 node is the only legitimate caller.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, CustomThunk, Category="Beam|Analytics",
		meta=(CustomStructureParam="EventStruct"))
	bool K2_EnqueueAnalyticsEvent(FUserSlot Slot,
		const FString& BlueprintCallsiteFile, int32 BlueprintCallsiteLine, const FString& BlueprintCallsiteFunction,
		const int32& EventStruct);
	DECLARE_FUNCTION(execK2_EnqueueAnalyticsEvent);

private:
	// --------------------------------------------------- 6. Private flush path

	bool TickFlush(float DeltaTime);
	void DoFlush();
	void PostAnalyticsBatch(const FUserSlot& Slot, const TArray<TSharedRef<FJsonObject>>& Events);

	// --------------------------------------------------- 7. Private utilities

	const FBeamAnalyticsEventConfig& ResolveConfig(const UScriptStruct* StructType) const;
	void HandleInvalidEvents(const UScriptStruct* StructType, const FBeamAnalyticsEventConfig& Config,
	                         TArray<FBeamAnalyticsEventEnvelope>& Invalid);

	// ------------------------------------------------------------------ 8. State

	UPROPERTY(Transient)
	TObjectPtr<UBeamUserSlots> UserSlots = nullptr;

	/** Memory-mapped ring file. All ring mechanics live in BeamMappedFile. */
	FBeamMappedFile RingFile;

	/** MPSC overflow queue (multiple writers, single drainer = the flusher). */
	TQueue<FBeamAnalyticsEventEnvelope, EQueueMode::Mpsc> PendingQueue;

	TMap<FName, UScriptStruct*>                          TypeCacheByName;
	TArray<UScriptStruct*>                               KnownEventTypes;
	TMap<UScriptStruct*, FBeamAnalyticsEventConfig>      ConfigCache;
	TMap<const UScriptStruct*, FBeamInvalidEventHandler> InvalidHandlers;

	int8 bFlushInFlight = 0;
	FTSTicker::FDelegateHandle TickHandle;
};


// =============================================================================
// Callsite-capture macros
// -----------------------------------------------------------------------------
//   BEAM_ENQUEUE_ANALYTICS_EVENT(UBeamAnalyticsSubsystem::GetSelf(this),
//                                FMyEvent{ .Score = 42 });
//
// `this` (or any UObject with a UWorld) provides the world context for GetSelf
// to resolve the per-UGameInstance subsystem instance.
// =============================================================================

#define BEAM_ENQUEUE_ANALYTICS_EVENT(Subsystem, Event) \
	(Subsystem)->EnqueueEvent((Event), BEAM_ANALYTICS_CALLSITE())

#define BEAM_ENQUEUE_ANALYTICS_EVENT_FOR_SLOT(Subsystem, Slot, Event) \
	(Subsystem)->EnqueueEventForSlot((Slot), (Event), BEAM_ANALYTICS_CALLSITE())
