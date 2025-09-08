#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlansResponse.h"

#include "ServicePlanActorServicePlansResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServicePlanActorServicePlansResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Json", DisplayName="ServicePlanActorServicePlansResponse To JSON String")
	static FString ServicePlanActorServicePlansResponseToJsonString(const UServicePlanActorServicePlansResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make ServicePlanActorServicePlansResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Plans, Outer", NativeMakeFunc))
	static UServicePlanActorServicePlansResponse* Make(FOptionalArrayOfServicePlanActorServicePlan Plans, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Break ServicePlanActorServicePlansResponse", meta=(NativeBreakFunc))
	static void Break(const UServicePlanActorServicePlansResponse* Serializable, FOptionalArrayOfServicePlanActorServicePlan& Plans);
};