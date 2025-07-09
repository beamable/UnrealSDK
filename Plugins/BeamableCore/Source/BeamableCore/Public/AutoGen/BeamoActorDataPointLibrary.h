#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoActorDataPoint.h"

#include "BeamoActorDataPointLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoActorDataPointLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoActorDataPoint To JSON String")
	static FString BeamoActorDataPointToJsonString(const UBeamoActorDataPoint* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoActorDataPoint", meta=(DefaultToSelf="Outer", AdvancedDisplay="TimeStamp, Outer", NativeMakeFunc))
	static UBeamoActorDataPoint* Make(double Value, FOptionalDateTime TimeStamp, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoActorDataPoint", meta=(NativeBreakFunc))
	static void Break(const UBeamoActorDataPoint* Serializable, double& Value, FOptionalDateTime& TimeStamp);
};