

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfCurrencyChange.h"

#include "OptionalArrayOfCurrencyChangeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfCurrencyChangeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfCurrencyChange MakeOptionalArrayOfCurrencyChange(TArray<UCurrencyChange*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UCurrencyChange*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfCurrencyChange Conv_OptionalArrayOfCurrencyChangeFromValue(TArray<UCurrencyChange*> Value);
};
