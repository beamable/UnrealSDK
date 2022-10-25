

#include "AutoGen/Optionals/OptionalMailRewardsLibrary.h"

FOptionalMailRewards UOptionalMailRewardsLibrary::MakeOptional(UMailRewards* Value)
{
	FOptionalMailRewards Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMailRewards UOptionalMailRewardsLibrary::Conv_OptionalFromValue(UMailRewards* Value)
{
	FOptionalMailRewards Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMailRewardsLibrary::HasValue(const FOptionalMailRewards& Optional, UMailRewards*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UMailRewards* UOptionalMailRewardsLibrary::GetOptionalValue(const FOptionalMailRewards& Optional, UMailRewards* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

