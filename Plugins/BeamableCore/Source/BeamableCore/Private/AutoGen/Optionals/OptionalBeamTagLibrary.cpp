

#include "AutoGen/Optionals/OptionalBeamTagLibrary.h"

FOptionalBeamTag UOptionalBeamTagLibrary::MakeOptional(FBeamTag Value)
{
	FOptionalBeamTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamTag UOptionalBeamTagLibrary::Conv_OptionalFromValue(FBeamTag Value)
{
	FOptionalBeamTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamTagLibrary::HasValue(const FOptionalBeamTag& Optional, FBeamTag& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamTag UOptionalBeamTagLibrary::GetOptionalValue(const FOptionalBeamTag& Optional, FBeamTag DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

