

#include "OptionalEventGroupRewardsLibrary.h"

FOptionalEventGroupRewards UOptionalEventGroupRewardsLibrary::MakeOptionalEventGroupRewards(UEventGroupRewards* Value)
{
	FOptionalEventGroupRewards Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEventGroupRewards UOptionalEventGroupRewardsLibrary::Conv_OptionalEventGroupRewardsFromValue(UEventGroupRewards* Value)
{
	FOptionalEventGroupRewards Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

