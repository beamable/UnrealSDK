

#include "AutoGen/Optionals/OptionalPlayerRewardLibrary.h"

FOptionalPlayerReward UOptionalPlayerRewardLibrary::MakeOptional(UPlayerReward* Value)
{
	FOptionalPlayerReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalPlayerReward UOptionalPlayerRewardLibrary::Conv_OptionalFromValue(UPlayerReward* Value)
{
	FOptionalPlayerReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalPlayerRewardLibrary::HasValue(const FOptionalPlayerReward& Optional, UPlayerReward*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UPlayerReward* UOptionalPlayerRewardLibrary::GetOptionalValue(const FOptionalPlayerReward& Optional, UPlayerReward* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

