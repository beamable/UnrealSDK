

#include "OptionalArrayOfEventInventoryRewardCurrencyLibrary.h"

FOptionalArrayOfEventInventoryRewardCurrency UOptionalArrayOfEventInventoryRewardCurrencyLibrary::MakeOptionalArrayOfEventInventoryRewardCurrency(TArray<UEventInventoryRewardCurrency*> Value)
{
	FOptionalArrayOfEventInventoryRewardCurrency Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventInventoryRewardCurrency UOptionalArrayOfEventInventoryRewardCurrencyLibrary::Conv_OptionalArrayOfEventInventoryRewardCurrencyFromValue(TArray<UEventInventoryRewardCurrency*> Value)
{
	FOptionalArrayOfEventInventoryRewardCurrency Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

