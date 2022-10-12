

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfEventInventoryRewardCurrency.h"

#include "OptionalArrayOfEventInventoryRewardCurrencyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfEventInventoryRewardCurrencyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfEventInventoryRewardCurrency MakeOptionalArrayOfEventInventoryRewardCurrency(TArray<UEventInventoryRewardCurrency*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UEventInventoryRewardCurrency*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfEventInventoryRewardCurrency Conv_OptionalArrayOfEventInventoryRewardCurrencyFromValue(TArray<UEventInventoryRewardCurrency*> Value);
};
