

#include "AutoGen/Optionals/OptionalBeamCidLibrary.h"

FOptionalBeamCid UOptionalBeamCidLibrary::MakeOptional(FBeamCid Value)
{
	FOptionalBeamCid Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamCid UOptionalBeamCidLibrary::Conv_OptionalFromValue(FBeamCid Value)
{
	FOptionalBeamCid Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamCidLibrary::HasValue(const FOptionalBeamCid& Optional, FBeamCid& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamCid UOptionalBeamCidLibrary::GetOptionalValue(const FOptionalBeamCid& Optional, FBeamCid DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

