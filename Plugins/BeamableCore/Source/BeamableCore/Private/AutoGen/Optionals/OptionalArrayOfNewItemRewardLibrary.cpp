

#include "AutoGen/Optionals/OptionalArrayOfNewItemRewardLibrary.h"

FOptionalArrayOfNewItemReward UOptionalArrayOfNewItemRewardLibrary::MakeOptional(TArray<UNewItemReward*> Value)
{
	FOptionalArrayOfNewItemReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfNewItemReward UOptionalArrayOfNewItemRewardLibrary::Conv_OptionalFromValue(TArray<UNewItemReward*> Value)
{
	FOptionalArrayOfNewItemReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfNewItemRewardLibrary::HasValue(const FOptionalArrayOfNewItemReward& Optional, TArray<UNewItemReward*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UNewItemReward*> UOptionalArrayOfNewItemRewardLibrary::GetOptionalValue(const FOptionalArrayOfNewItemReward& Optional, TArray<UNewItemReward*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

