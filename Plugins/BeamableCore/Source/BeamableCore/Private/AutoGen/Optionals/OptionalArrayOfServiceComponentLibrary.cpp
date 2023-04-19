

#include "AutoGen/Optionals/OptionalArrayOfServiceComponentLibrary.h"

FOptionalArrayOfServiceComponent UOptionalArrayOfServiceComponentLibrary::MakeOptional(TArray<UServiceComponent*> Value)
{
	FOptionalArrayOfServiceComponent Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceComponent UOptionalArrayOfServiceComponentLibrary::Conv_OptionalFromValue(TArray<UServiceComponent*> Value)
{
	FOptionalArrayOfServiceComponent Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfServiceComponentLibrary::HasValue(const FOptionalArrayOfServiceComponent& Optional, TArray<UServiceComponent*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UServiceComponent*> UOptionalArrayOfServiceComponentLibrary::GetOptionalValue(const FOptionalArrayOfServiceComponent& Optional, TArray<UServiceComponent*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

