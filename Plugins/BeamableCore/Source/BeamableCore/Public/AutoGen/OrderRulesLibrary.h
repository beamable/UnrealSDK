
#pragma once

#include "CoreMinimal.h"
#include "OrderRules.h"

#include "OrderRulesLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UOrderRulesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize OrderRules To JSON String")
	static FString OrderRulesToJsonString(const UOrderRules* Serializable, const bool Pretty);		
};