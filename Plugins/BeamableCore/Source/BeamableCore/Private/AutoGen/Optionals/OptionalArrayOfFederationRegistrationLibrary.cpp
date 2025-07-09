

#include "AutoGen/Optionals/OptionalArrayOfFederationRegistrationLibrary.h"

FOptionalArrayOfFederationRegistration UOptionalArrayOfFederationRegistrationLibrary::MakeOptional(TArray<UFederationRegistration*> Value)
{
	FOptionalArrayOfFederationRegistration Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfFederationRegistration UOptionalArrayOfFederationRegistrationLibrary::Conv_OptionalFromValue(TArray<UFederationRegistration*> Value)
{
	FOptionalArrayOfFederationRegistration Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfFederationRegistrationLibrary::HasValue(const FOptionalArrayOfFederationRegistration& Optional, TArray<UFederationRegistration*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UFederationRegistration*> UOptionalArrayOfFederationRegistrationLibrary::GetOptionalValue(const FOptionalArrayOfFederationRegistration& Optional, TArray<UFederationRegistration*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

