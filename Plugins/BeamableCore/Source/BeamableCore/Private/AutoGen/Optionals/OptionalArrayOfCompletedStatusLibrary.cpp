

#include "AutoGen/Optionals/OptionalArrayOfCompletedStatusLibrary.h"

FOptionalArrayOfCompletedStatus UOptionalArrayOfCompletedStatusLibrary::MakeOptional(TArray<UCompletedStatus*> Value)
{
	FOptionalArrayOfCompletedStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCompletedStatus UOptionalArrayOfCompletedStatusLibrary::Conv_OptionalFromValue(TArray<UCompletedStatus*> Value)
{
	FOptionalArrayOfCompletedStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfCompletedStatusLibrary::HasValue(const FOptionalArrayOfCompletedStatus& Optional, TArray<UCompletedStatus*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UCompletedStatus*> UOptionalArrayOfCompletedStatusLibrary::GetOptionalValue(const FOptionalArrayOfCompletedStatus& Optional, TArray<UCompletedStatus*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

