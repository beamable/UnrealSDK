

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalMapOfArrayOfCurrencyProperty.h"

#include "OptionalMapOfArrayOfCurrencyPropertyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMapOfArrayOfCurrencyPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalMapOfArrayOfCurrencyProperty MakeOptionalMapOfArrayOfCurrencyProperty(TMap<FString, FArrayOfCurrencyProperty> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TMap<FString, FArrayOfCurrencyProperty> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalMapOfArrayOfCurrencyProperty Conv_OptionalMapOfArrayOfCurrencyPropertyFromValue(TMap<FString, FArrayOfCurrencyProperty> Value);
};
