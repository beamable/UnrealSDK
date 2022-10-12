
#pragma once

#include "CoreMinimal.h"
#include "OrderRule.h"

#include "OrderRuleLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UOrderRuleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize OrderRule To JSON String")
	static FString OrderRuleToJsonString(const UOrderRule* Serializable, const bool Pretty);		
};