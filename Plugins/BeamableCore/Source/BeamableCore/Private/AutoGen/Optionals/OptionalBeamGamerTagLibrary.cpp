

#include "AutoGen/Optionals/OptionalBeamGamerTagLibrary.h"

FOptionalBeamGamerTag UOptionalBeamGamerTagLibrary::MakeOptional(FBeamGamerTag Value)
{
	FOptionalBeamGamerTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamGamerTag UOptionalBeamGamerTagLibrary::Conv_OptionalFromValue(FBeamGamerTag Value)
{
	FOptionalBeamGamerTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamGamerTagLibrary::HasValue(const FOptionalBeamGamerTag& Optional, FBeamGamerTag& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamGamerTag UOptionalBeamGamerTagLibrary::GetOptionalValue(const FOptionalBeamGamerTag& Optional, FBeamGamerTag DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

