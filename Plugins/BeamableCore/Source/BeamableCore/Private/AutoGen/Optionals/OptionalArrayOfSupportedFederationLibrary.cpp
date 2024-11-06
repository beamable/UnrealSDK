

#include "AutoGen/Optionals/OptionalArrayOfSupportedFederationLibrary.h"

FOptionalArrayOfSupportedFederation UOptionalArrayOfSupportedFederationLibrary::MakeOptional(TArray<USupportedFederation*> Value)
{
	FOptionalArrayOfSupportedFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfSupportedFederation UOptionalArrayOfSupportedFederationLibrary::Conv_OptionalFromValue(TArray<USupportedFederation*> Value)
{
	FOptionalArrayOfSupportedFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfSupportedFederationLibrary::HasValue(const FOptionalArrayOfSupportedFederation& Optional, TArray<USupportedFederation*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<USupportedFederation*> UOptionalArrayOfSupportedFederationLibrary::GetOptionalValue(const FOptionalArrayOfSupportedFederation& Optional, TArray<USupportedFederation*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

