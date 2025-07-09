#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetMetricsRequestBody.h"

#include "GetMetricsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetMetricsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="GetMetricsRequestBody To JSON String")
	static FString GetMetricsRequestBodyToJsonString(const UGetMetricsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetMetricsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="MetricName, StartTime, EndTime, Period, Outer", NativeMakeFunc))
	static UGetMetricsRequestBody* Make(FOptionalString MetricName, FOptionalDateTime StartTime, FOptionalDateTime EndTime, FOptionalInt32 Period, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break GetMetricsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetMetricsRequestBody* Serializable, FOptionalString& MetricName, FOptionalDateTime& StartTime, FOptionalDateTime& EndTime, FOptionalInt32& Period);
};