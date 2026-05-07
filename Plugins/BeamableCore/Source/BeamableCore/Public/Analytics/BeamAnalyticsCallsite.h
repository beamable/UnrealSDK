#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "Serialization/BeamJsonSerializable.h"

#include "BeamAnalyticsCallsite.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamAnalyticsCallsite : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString File;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Line = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Function;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double TimestampUtcSeconds = 0.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString UserSlot;

	FBeamAnalyticsCallsite() = default;
	FBeamAnalyticsCallsite(const FString& InFile, int32 InLine, const FString& InFunction,
		double InTimestampUtcSeconds, const FString& InUserSlot)
		: File(InFile)
		, Line(InLine)
		, Function(InFunction)
		, TimestampUtcSeconds(InTimestampUtcSeconds)
		, UserSlot(InUserSlot)
	{
	}
};

#define BEAM_ANALYTICS_CALLSITE() \
	FBeamAnalyticsCallsite( \
		FString(ANSI_TO_TCHAR(__FILE__)), \
		static_cast<int32>(__LINE__), \
		FString(ANSI_TO_TCHAR(__FUNCTION__)), \
		FDateTime::UtcNow().ToUnixTimestampDecimal(), \
		FString())
