

#include "AutoGen/Optionals/OptionalActivationStatusLibrary.h"

FOptionalActivationStatus UOptionalActivationStatusLibrary::MakeOptional(EBeamActivationStatus Value)
{
	FOptionalActivationStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalActivationStatus UOptionalActivationStatusLibrary::Conv_OptionalFromValue(EBeamActivationStatus Value)
{
	FOptionalActivationStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalActivationStatusLibrary::HasValue(const FOptionalActivationStatus& Optional, EBeamActivationStatus& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamActivationStatus UOptionalActivationStatusLibrary::GetOptionalValue(const FOptionalActivationStatus& Optional, EBeamActivationStatus DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

