

#include "AutoGen/Optionals/OptionalArrayOfCurrencyChangeRewardLibrary.h"

FOptionalArrayOfCurrencyChangeReward UOptionalArrayOfCurrencyChangeRewardLibrary::MakeOptional(TArray<UCurrencyChangeReward*> Value)
{
	FOptionalArrayOfCurrencyChangeReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCurrencyChangeReward UOptionalArrayOfCurrencyChangeRewardLibrary::Conv_OptionalFromValue(TArray<UCurrencyChangeReward*> Value)
{
	FOptionalArrayOfCurrencyChangeReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfCurrencyChangeRewardLibrary::HasValue(const FOptionalArrayOfCurrencyChangeReward& Optional, TArray<UCurrencyChangeReward*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UCurrencyChangeReward*> UOptionalArrayOfCurrencyChangeRewardLibrary::GetOptionalValue(const FOptionalArrayOfCurrencyChangeReward& Optional, TArray<UCurrencyChangeReward*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

