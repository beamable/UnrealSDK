#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorServiceLimits.h"

#include "ServicePlanActorServiceLimitsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServicePlanActorServiceLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Json", DisplayName="ServicePlanActorServiceLimits To JSON String")
	static FString ServicePlanActorServiceLimitsToJsonString(const UServicePlanActorServiceLimits* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make ServicePlanActorServiceLimits", meta=(DefaultToSelf="Outer", AdvancedDisplay="Beamo, Outer", NativeMakeFunc))
	static UServicePlanActorServiceLimits* Make(FOptionalServicePlanActorBeamoLimits Beamo, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Break ServicePlanActorServiceLimits", meta=(NativeBreakFunc))
	static void Break(const UServicePlanActorServiceLimits* Serializable, FOptionalServicePlanActorBeamoLimits& Beamo);
};