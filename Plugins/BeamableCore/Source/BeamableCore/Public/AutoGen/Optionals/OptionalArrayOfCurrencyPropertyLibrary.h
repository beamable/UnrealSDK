

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfCurrencyProperty.h"

#include "OptionalArrayOfCurrencyPropertyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfCurrencyPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfCurrencyProperty MakeOptionalArrayOfCurrencyProperty(TArray<UCurrencyProperty*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UCurrencyProperty*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfCurrencyProperty Conv_OptionalArrayOfCurrencyPropertyFromValue(TArray<UCurrencyProperty*> Value);
};
