#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Analytics/BeamAnalyticsCallsite.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonWriter.h"

#include "BeamAnalyticsEvent.generated.h"

UENUM(BlueprintType)
enum class EBeamAnalyticsLogVerbosity : uint8
{
	NoLogging,
	Fatal,
	Error,
	Warning,
	Display,
	Log,
	Verbose,
	VeryVerbose
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamValidatorTree
{
	GENERATED_BODY()
};

/**
 * Base class for any analytics event sent through UBeamAnalyticsSubsystem.
 *
 * Subtypes override the virtuals to specify wire-format identifiers:
 *   - GetOpCode    -> "op"   field of the batch event (defaults to "g.core")
 *   - GetCategory  -> "c"    field
 *   - GetEventName -> "e"    field
 *   - BuildParamsJsonString -> "p" field payload (defaults to the struct's BeamSerialize)
 *
 * The wire format on /report/custom_batch is exactly:
 *   { "op": <op>, "c": <category>, "e": <event-name>, "p": <params-object> }
 * Callsite info is embedded inside "p" when the per-event config requests it.
 */
USTRUCT(BlueprintType, meta=(BeamAnalyticsEventBase))
struct BEAMABLECORE_API FBeamAnalyticsEvent : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	/** Schema version of the event payload. Subtypes override the default value
	    whenever they change the shape of their fields. Used at MMF recovery to
	    drop envelopes whose schema no longer matches the current type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Analytics")
	FString Version = TEXT("1.0.0");

	virtual FBeamValidatorTree GetValidatorTree() const { return FBeamValidatorTree{}; }

	virtual FString GetOpCode()    const { return TEXT("g.core"); }
	virtual FString GetCategory()  const { return TEXT(""); }
	virtual FString GetEventName() const { return TEXT(""); }

	/**
	 * Produce the JSON string for the "p" field. Default implementation serializes
	 * all of this struct's properties via BeamSerialize. Override to feed a custom
	 * payload (FBeamAnalyticsLegacyEvent does this to forward the user's pre-built
	 * params JSON).
	 */
	virtual void BuildParamsJsonString(FString& Out) const
	{
		auto Writer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Out);
		this->BeamSerialize(Writer);
		Writer->Close();
	}
};

/**
 * Internal envelope written into the ring buffer. Contains the wire-format identifiers
 * captured at enqueue time + the params JSON string + the callsite JSON string.
 * The flusher reads these directly to assemble the outgoing batch.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamAnalyticsEventEnvelope
{
	GENERATED_BODY()

	UPROPERTY() FString TypeName;
	UPROPERTY() FString SchemaVersion;
	UPROPERTY() FString OpCode;
	UPROPERTY() FString Category;
	UPROPERTY() FString EventName;
	UPROPERTY() FString CallsiteJson;
	UPROPERTY() FString PayloadJson;
	UPROPERTY() FString UserSlot;
};

UENUM(BlueprintType)
enum class EBeamInvalidEventBehavior : uint8
{
	Drop,
	LogOnly,
	SendAsIs,
	EnsureOrCheck,
	Custom
};

/** Controls whether callsite debugging info is embedded inside "p" at flush time. */
UENUM(BlueprintType)
enum class EBeamAnalyticsCallsiteInclusion : uint8
{
	/** Never embed callsite info. */
	Never,
	/** Embed callsite info only on events that failed validation. */
	OnInvalidOnly,
	/** Embed callsite info on every emitted event. */
	Always
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamAnalyticsEventConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(MetaStruct="/Script/BeamableCore.BeamAnalyticsEvent"))
	TObjectPtr<UScriptStruct> EventType = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin="0.0", ClampMax="1.0"))
	float SampleRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EBeamInvalidEventBehavior InvalidBehavior = EBeamInvalidEventBehavior::Drop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EBeamAnalyticsLogVerbosity LogVerbosity = EBeamAnalyticsLogVerbosity::Warning;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseEnsureNotCheck = true;

	/** Whether to embed callsite info into the "p" payload at flush time. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EBeamAnalyticsCallsiteInclusion CallsiteInclusion = EBeamAnalyticsCallsiteInclusion::Never;
};
