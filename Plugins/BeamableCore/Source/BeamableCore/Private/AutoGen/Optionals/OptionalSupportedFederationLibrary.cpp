

#include "AutoGen/Optionals/OptionalSupportedFederationLibrary.h"

FOptionalSupportedFederation UOptionalSupportedFederationLibrary::MakeOptional(USupportedFederation* Value)
{
	FOptionalSupportedFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalSupportedFederation UOptionalSupportedFederationLibrary::Conv_OptionalFromValue(USupportedFederation* Value)
{
	FOptionalSupportedFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalSupportedFederationLibrary::HasValue(const FOptionalSupportedFederation& Optional, USupportedFederation*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

USupportedFederation* UOptionalSupportedFederationLibrary::GetOptionalValue(const FOptionalSupportedFederation& Optional, USupportedFederation* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

