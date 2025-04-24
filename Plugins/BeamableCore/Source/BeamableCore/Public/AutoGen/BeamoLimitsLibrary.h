#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoLimits.h"

#include "BeamoLimitsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="BeamoLimits To JSON String")
	static FString BeamoLimitsToJsonString(const UBeamoLimits* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make BeamoLimits", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoLimits* Make(FString MaxContainerSize, int32 MaxRunningContainersPerService, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break BeamoLimits", meta=(NativeBreakFunc))
	static void Break(const UBeamoLimits* Serializable, FString& MaxContainerSize, int32& MaxRunningContainersPerService);
};