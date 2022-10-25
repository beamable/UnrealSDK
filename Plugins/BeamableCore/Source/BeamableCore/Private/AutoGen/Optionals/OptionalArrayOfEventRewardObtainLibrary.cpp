

#include "AutoGen/Optionals/OptionalArrayOfEventRewardObtainLibrary.h"

FOptionalArrayOfEventRewardObtain UOptionalArrayOfEventRewardObtainLibrary::MakeOptional(TArray<UEventRewardObtain*> Value)
{
	FOptionalArrayOfEventRewardObtain Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventRewardObtain UOptionalArrayOfEventRewardObtainLibrary::Conv_OptionalFromValue(TArray<UEventRewardObtain*> Value)
{
	FOptionalArrayOfEventRewardObtain Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfEventRewardObtainLibrary::HasValue(const FOptionalArrayOfEventRewardObtain& Optional, TArray<UEventRewardObtain*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UEventRewardObtain*> UOptionalArrayOfEventRewardObtainLibrary::GetOptionalValue(const FOptionalArrayOfEventRewardObtain& Optional, TArray<UEventRewardObtain*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

