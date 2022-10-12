

#include "OptionalArrayOfCurrencyChangeRewardLibrary.h"

FOptionalArrayOfCurrencyChangeReward UOptionalArrayOfCurrencyChangeRewardLibrary::MakeOptionalArrayOfCurrencyChangeReward(TArray<UCurrencyChangeReward*> Value)
{
	FOptionalArrayOfCurrencyChangeReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCurrencyChangeReward UOptionalArrayOfCurrencyChangeRewardLibrary::Conv_OptionalArrayOfCurrencyChangeRewardFromValue(TArray<UCurrencyChangeReward*> Value)
{
	FOptionalArrayOfCurrencyChangeReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

