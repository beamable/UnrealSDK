

#include "OptionalArrayOfCompletedStatusLibrary.h"

FOptionalArrayOfCompletedStatus UOptionalArrayOfCompletedStatusLibrary::MakeOptionalArrayOfCompletedStatus(TArray<UCompletedStatus*> Value)
{
	FOptionalArrayOfCompletedStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCompletedStatus UOptionalArrayOfCompletedStatusLibrary::Conv_OptionalArrayOfCompletedStatusFromValue(TArray<UCompletedStatus*> Value)
{
	FOptionalArrayOfCompletedStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

