#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicBeamoLimits.h"

#include "RealmsBasicBeamoLimitsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicBeamoLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicBeamoLimits To JSON String")
	static FString RealmsBasicBeamoLimitsToJsonString(const URealmsBasicBeamoLimits* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicBeamoLimits", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmsBasicBeamoLimits* Make(FString MaxContainerSize, int32 MaxRunningContainersPerService, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicBeamoLimits", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicBeamoLimits* Serializable, FString& MaxContainerSize, int32& MaxRunningContainersPerService);
};