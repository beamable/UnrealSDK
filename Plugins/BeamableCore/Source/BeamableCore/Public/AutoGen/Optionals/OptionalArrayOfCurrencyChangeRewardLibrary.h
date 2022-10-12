

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfCurrencyChangeReward.h"

#include "OptionalArrayOfCurrencyChangeRewardLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfCurrencyChangeRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfCurrencyChangeReward MakeOptionalArrayOfCurrencyChangeReward(TArray<UCurrencyChangeReward*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UCurrencyChangeReward*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfCurrencyChangeReward Conv_OptionalArrayOfCurrencyChangeRewardFromValue(TArray<UCurrencyChangeReward*> Value);
};
