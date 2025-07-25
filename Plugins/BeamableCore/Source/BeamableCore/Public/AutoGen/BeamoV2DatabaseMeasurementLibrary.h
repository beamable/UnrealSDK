#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2DatabaseMeasurement.h"

#include "BeamoV2DatabaseMeasurementLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2DatabaseMeasurementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2DatabaseMeasurement To JSON String")
	static FString BeamoV2DatabaseMeasurementToJsonString(const UBeamoV2DatabaseMeasurement* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2DatabaseMeasurement", meta=(DefaultToSelf="Outer", AdvancedDisplay="DataPoints, Outer", NativeMakeFunc))
	static UBeamoV2DatabaseMeasurement* Make(FString Name, FString Units, FOptionalArrayOfBeamoV2DataPoint DataPoints, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2DatabaseMeasurement", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2DatabaseMeasurement* Serializable, FString& Name, FString& Units, FOptionalArrayOfBeamoV2DataPoint& DataPoints);
};