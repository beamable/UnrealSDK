

#include "OptionalArrayOfEventRewardContentLibrary.h"

FOptionalArrayOfEventRewardContent UOptionalArrayOfEventRewardContentLibrary::MakeOptionalArrayOfEventRewardContent(TArray<UEventRewardContent*> Value)
{
	FOptionalArrayOfEventRewardContent Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventRewardContent UOptionalArrayOfEventRewardContentLibrary::Conv_OptionalArrayOfEventRewardContentFromValue(TArray<UEventRewardContent*> Value)
{
	FOptionalArrayOfEventRewardContent Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

