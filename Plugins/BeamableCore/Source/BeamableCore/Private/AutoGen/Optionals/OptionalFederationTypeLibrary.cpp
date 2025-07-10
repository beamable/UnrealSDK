

#include "AutoGen/Optionals/OptionalFederationTypeLibrary.h"

FOptionalFederationType UOptionalFederationTypeLibrary::MakeOptional(EBeamFederationType Value)
{
	FOptionalFederationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalFederationType UOptionalFederationTypeLibrary::Conv_OptionalFromValue(EBeamFederationType Value)
{
	FOptionalFederationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalFederationTypeLibrary::HasValue(const FOptionalFederationType& Optional, EBeamFederationType& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamFederationType UOptionalFederationTypeLibrary::GetOptionalValue(const FOptionalFederationType& Optional, EBeamFederationType DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

