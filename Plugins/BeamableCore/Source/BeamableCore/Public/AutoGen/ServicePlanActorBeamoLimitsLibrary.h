#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorBeamoLimits.h"

#include "ServicePlanActorBeamoLimitsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServicePlanActorBeamoLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Json", DisplayName="ServicePlanActorBeamoLimits To JSON String")
	static FString ServicePlanActorBeamoLimitsToJsonString(const UServicePlanActorBeamoLimits* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make ServicePlanActorBeamoLimits", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServicePlanActorBeamoLimits* Make(UObject* Outer);

	
};