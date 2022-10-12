

#include "OptionalArrayOfEventRewardObtainLibrary.h"

FOptionalArrayOfEventRewardObtain UOptionalArrayOfEventRewardObtainLibrary::MakeOptionalArrayOfEventRewardObtain(TArray<UEventRewardObtain*> Value)
{
	FOptionalArrayOfEventRewardObtain Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventRewardObtain UOptionalArrayOfEventRewardObtainLibrary::Conv_OptionalArrayOfEventRewardObtainFromValue(TArray<UEventRewardObtain*> Value)
{
	FOptionalArrayOfEventRewardObtain Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

