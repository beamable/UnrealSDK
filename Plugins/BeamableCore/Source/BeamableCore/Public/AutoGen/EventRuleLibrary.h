
#pragma once

#include "CoreMinimal.h"
#include "EventRule.h"

#include "EventRuleLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventRuleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventRule To JSON String")
	static FString EventRuleToJsonString(const UEventRule* Serializable, const bool Pretty);		
};