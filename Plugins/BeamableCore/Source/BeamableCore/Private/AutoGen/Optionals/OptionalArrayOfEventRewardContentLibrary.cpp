

#include "AutoGen/Optionals/OptionalArrayOfEventRewardContentLibrary.h"

FOptionalArrayOfEventRewardContent UOptionalArrayOfEventRewardContentLibrary::MakeOptional(TArray<UEventRewardContent*> Value)
{
	FOptionalArrayOfEventRewardContent Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventRewardContent UOptionalArrayOfEventRewardContentLibrary::Conv_OptionalFromValue(TArray<UEventRewardContent*> Value)
{
	FOptionalArrayOfEventRewardContent Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfEventRewardContentLibrary::HasValue(const FOptionalArrayOfEventRewardContent& Optional, TArray<UEventRewardContent*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UEventRewardContent*> UOptionalArrayOfEventRewardContentLibrary::GetOptionalValue(const FOptionalArrayOfEventRewardContent& Optional, TArray<UEventRewardContent*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

