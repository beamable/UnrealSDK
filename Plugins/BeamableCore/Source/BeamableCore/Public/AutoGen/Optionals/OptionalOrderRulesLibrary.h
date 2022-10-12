

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalOrderRules.h"

#include "OptionalOrderRulesLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalOrderRulesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalOrderRules MakeOptionalOrderRules(UOrderRules* Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "OrderRules To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalOrderRules Conv_OptionalOrderRulesFromValue(UOrderRules* Value);
};
