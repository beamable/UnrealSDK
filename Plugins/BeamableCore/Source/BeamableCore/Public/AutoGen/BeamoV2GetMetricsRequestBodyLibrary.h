#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetMetricsRequestBody.h"

#include "BeamoV2GetMetricsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2GetMetricsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2GetMetricsRequestBody To JSON String")
	static FString BeamoV2GetMetricsRequestBodyToJsonString(const UBeamoV2GetMetricsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2GetMetricsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="MetricName, StartTime, EndTime, Period, Outer", NativeMakeFunc))
	static UBeamoV2GetMetricsRequestBody* Make(FOptionalString MetricName, FOptionalDateTime StartTime, FOptionalDateTime EndTime, FOptionalInt32 Period, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2GetMetricsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2GetMetricsRequestBody* Serializable, FOptionalString& MetricName, FOptionalDateTime& StartTime, FOptionalDateTime& EndTime, FOptionalInt32& Period);
};