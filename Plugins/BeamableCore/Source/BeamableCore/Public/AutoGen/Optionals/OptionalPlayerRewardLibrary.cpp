

#include "OptionalPlayerRewardLibrary.h"

FOptionalPlayerReward UOptionalPlayerRewardLibrary::MakeOptionalPlayerReward(UPlayerReward* Value)
{
	FOptionalPlayerReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalPlayerReward UOptionalPlayerRewardLibrary::Conv_OptionalPlayerRewardFromValue(UPlayerReward* Value)
{
	FOptionalPlayerReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

