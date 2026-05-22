#pragma once

#pragma once

#include "CoreMinimal.h"

#include "BeamAnalyticsEventConfig.generated.h"

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
