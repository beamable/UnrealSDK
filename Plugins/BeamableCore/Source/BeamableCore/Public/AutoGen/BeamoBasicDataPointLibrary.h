#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoBasicDataPoint.h"

#include "BeamoBasicDataPointLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoBasicDataPointLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoBasicDataPoint To JSON String")
	static FString BeamoBasicDataPointToJsonString(const UBeamoBasicDataPoint* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoBasicDataPoint", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoBasicDataPoint* Make(FString Timestamp, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoBasicDataPoint", meta=(NativeBreakFunc))
	static void Break(const UBeamoBasicDataPoint* Serializable, FString& Timestamp, FString& Value);
};