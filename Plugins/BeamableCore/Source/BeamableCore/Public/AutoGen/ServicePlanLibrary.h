
#pragma once

#include "CoreMinimal.h"
#include "ServicePlan.h"

#include "ServicePlanLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServicePlanLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServicePlan To JSON String")
	static FString ServicePlanToJsonString(const UServicePlan* Serializable, const bool Pretty);		
};