

#include "AutoGen/Optionals/OptionalArrayOfServiceRegistrationLibrary.h"

FOptionalArrayOfServiceRegistration UOptionalArrayOfServiceRegistrationLibrary::MakeOptional(TArray<UServiceRegistration*> Value)
{
	FOptionalArrayOfServiceRegistration Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceRegistration UOptionalArrayOfServiceRegistrationLibrary::Conv_OptionalFromValue(TArray<UServiceRegistration*> Value)
{
	FOptionalArrayOfServiceRegistration Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfServiceRegistrationLibrary::HasValue(const FOptionalArrayOfServiceRegistration& Optional, TArray<UServiceRegistration*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UServiceRegistration*> UOptionalArrayOfServiceRegistrationLibrary::GetOptionalValue(const FOptionalArrayOfServiceRegistration& Optional, TArray<UServiceRegistration*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

