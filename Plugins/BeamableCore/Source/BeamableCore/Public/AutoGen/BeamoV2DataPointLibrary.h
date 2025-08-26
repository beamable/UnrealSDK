#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2DataPoint.h"

#include "BeamoV2DataPointLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2DataPointLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2DataPoint To JSON String")
	static FString BeamoV2DataPointToJsonString(const UBeamoV2DataPoint* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2DataPoint", meta=(DefaultToSelf="Outer", AdvancedDisplay="TimeStamp, Outer", NativeMakeFunc))
	static UBeamoV2DataPoint* Make(double Value, FOptionalDateTime TimeStamp, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2DataPoint", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2DataPoint* Serializable, double& Value, FOptionalDateTime& TimeStamp);
};