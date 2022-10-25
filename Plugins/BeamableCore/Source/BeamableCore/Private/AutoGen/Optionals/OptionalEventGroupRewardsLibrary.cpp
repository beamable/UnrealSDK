

#include "AutoGen/Optionals/OptionalEventGroupRewardsLibrary.h"

FOptionalEventGroupRewards UOptionalEventGroupRewardsLibrary::MakeOptional(UEventGroupRewards* Value)
{
	FOptionalEventGroupRewards Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEventGroupRewards UOptionalEventGroupRewardsLibrary::Conv_OptionalFromValue(UEventGroupRewards* Value)
{
	FOptionalEventGroupRewards Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalEventGroupRewardsLibrary::HasValue(const FOptionalEventGroupRewards& Optional, UEventGroupRewards*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UEventGroupRewards* UOptionalEventGroupRewardsLibrary::GetOptionalValue(const FOptionalEventGroupRewards& Optional, UEventGroupRewards* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

