

#include "AutoGen/Optionals/OptionalArrayOfEventInventoryRewardCurrencyLibrary.h"

FOptionalArrayOfEventInventoryRewardCurrency UOptionalArrayOfEventInventoryRewardCurrencyLibrary::MakeOptional(TArray<UEventInventoryRewardCurrency*> Value)
{
	FOptionalArrayOfEventInventoryRewardCurrency Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventInventoryRewardCurrency UOptionalArrayOfEventInventoryRewardCurrencyLibrary::Conv_OptionalFromValue(TArray<UEventInventoryRewardCurrency*> Value)
{
	FOptionalArrayOfEventInventoryRewardCurrency Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfEventInventoryRewardCurrencyLibrary::HasValue(const FOptionalArrayOfEventInventoryRewardCurrency& Optional, TArray<UEventInventoryRewardCurrency*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UEventInventoryRewardCurrency*> UOptionalArrayOfEventInventoryRewardCurrencyLibrary::GetOptionalValue(const FOptionalArrayOfEventInventoryRewardCurrency& Optional, TArray<UEventInventoryRewardCurrency*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

