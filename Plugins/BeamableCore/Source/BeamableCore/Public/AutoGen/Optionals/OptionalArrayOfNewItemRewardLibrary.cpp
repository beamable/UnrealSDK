

#include "OptionalArrayOfNewItemRewardLibrary.h"

FOptionalArrayOfNewItemReward UOptionalArrayOfNewItemRewardLibrary::MakeOptionalArrayOfNewItemReward(TArray<UNewItemReward*> Value)
{
	FOptionalArrayOfNewItemReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfNewItemReward UOptionalArrayOfNewItemRewardLibrary::Conv_OptionalArrayOfNewItemRewardFromValue(TArray<UNewItemReward*> Value)
{
	FOptionalArrayOfNewItemReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

