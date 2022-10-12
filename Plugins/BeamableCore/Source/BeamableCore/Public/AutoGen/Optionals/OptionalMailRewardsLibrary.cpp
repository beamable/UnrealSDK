

#include "OptionalMailRewardsLibrary.h"

FOptionalMailRewards UOptionalMailRewardsLibrary::MakeOptionalMailRewards(UMailRewards* Value)
{
	FOptionalMailRewards Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMailRewards UOptionalMailRewardsLibrary::Conv_OptionalMailRewardsFromValue(UMailRewards* Value)
{
	FOptionalMailRewards Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

