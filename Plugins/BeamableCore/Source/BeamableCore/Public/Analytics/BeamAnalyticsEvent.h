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

/**
 * Per-property validation result. Populated by generated event Validate()
 * overrides via BeamValidators helpers, then handed to FBeamValidationContext.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamValidationResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PropertyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ErrorCode;

	/** 0 = Error, 1 = Warning. Reserved; today the subsystem treats anything with errors as a failure. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Severity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SchemaPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Errors;

	FBeamValidationResult() = default;

	explicit FBeamValidationResult(const FString& InPropertyName)
		: PropertyName(InPropertyName) {}

	void AddError(const FString& Error, const FString& InErrorCode = TEXT(""))
	{
		Errors.Add(Error);
		if (!InErrorCode.IsEmpty()) ErrorCode = InErrorCode;
	}

	bool IsValid() const { return Errors.Num() == 0; }
};

/**
 * Aggregated pass/fail bucket populated by an event's Validate() override.
 * UBeamAnalyticsSubsystem builds one of these per envelope at flush time
 * to decide Valid vs Invalid routing.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamValidationContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBeamValidationResult> FailResults;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBeamValidationResult> PassResults;

	void RecordResult(const FBeamValidationResult& Result)
	{
		if (Result.IsValid()) PassResults.Add(Result);
		else                  FailResults.Add(Result);
	}

	bool IsValid()     const { return FailResults.Num() == 0; }
	bool HasFailures() const { return FailResults.Num() > 0;  }
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

	/**
	 * Run schema validation on this event. Default implementation is a no-op
	 * (everything passes). Generated subtypes override this to call into the
	 * BeamValidators namespace helpers and feed per-property results into OutContext.
	 *
	 * Invoked by UBeamAnalyticsSubsystem at flush time after deserializing the
	 * envelope's "p" payload back into a typed instance of the event.
	 */
	virtual void Validate(FBeamValidationContext& OutContext) const {}

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

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Version"), Version);
	}

	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("Version"), Version);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		if (Bag->HasField(TEXT("Version")))
			Version = Bag->GetStringField(TEXT("Version"));
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
