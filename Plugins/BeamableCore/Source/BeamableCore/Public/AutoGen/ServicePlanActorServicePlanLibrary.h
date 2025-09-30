#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlan.h"

#include "ServicePlanActorServicePlanLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServicePlanActorServicePlanLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Json", DisplayName="ServicePlanActorServicePlan To JSON String")
	static FString ServicePlanActorServicePlanToJsonString(const UServicePlanActorServicePlan* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make ServicePlanActorServicePlan", meta=(DefaultToSelf="Outer", AdvancedDisplay="ServiceLimits, Outer", NativeMakeFunc))
	static UServicePlanActorServicePlan* Make(FString Name, UServicePlanActorDataDomain* DataDomain, FOptionalServicePlanActorServiceLimits ServiceLimits, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Break ServicePlanActorServicePlan", meta=(NativeBreakFunc))
	static void Break(const UServicePlanActorServicePlan* Serializable, FString& Name, UServicePlanActorDataDomain*& DataDomain, FOptionalServicePlanActorServiceLimits& ServiceLimits);
};