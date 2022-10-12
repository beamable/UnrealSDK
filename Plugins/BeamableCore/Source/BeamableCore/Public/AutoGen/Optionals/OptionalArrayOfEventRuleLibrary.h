

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfEventRule.h"

#include "OptionalArrayOfEventRuleLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfEventRuleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfEventRule MakeOptionalArrayOfEventRule(TArray<UEventRule*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UEventRule*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfEventRule Conv_OptionalArrayOfEventRuleFromValue(TArray<UEventRule*> Value);
};
