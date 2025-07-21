#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2StartServiceLogsRequestBody.h"

#include "BeamoV2StartServiceLogsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2StartServiceLogsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2StartServiceLogsRequestBody To JSON String")
	static FString BeamoV2StartServiceLogsRequestBodyToJsonString(const UBeamoV2StartServiceLogsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2StartServiceLogsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ServiceName, StartTime, EndTime, Order, Limit, Filters, Outer", NativeMakeFunc))
	static UBeamoV2StartServiceLogsRequestBody* Make(FOptionalString ServiceName, FOptionalDateTime StartTime, FOptionalDateTime EndTime, FOptionalBeamoV2OrderDirection Order, FOptionalInt32 Limit, FOptionalArrayOfString Filters, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2StartServiceLogsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2StartServiceLogsRequestBody* Serializable, FOptionalString& ServiceName, FOptionalDateTime& StartTime, FOptionalDateTime& EndTime, FOptionalBeamoV2OrderDirection& Order, FOptionalInt32& Limit, FOptionalArrayOfString& Filters);
};