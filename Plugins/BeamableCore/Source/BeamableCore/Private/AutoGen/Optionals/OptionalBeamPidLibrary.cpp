

#include "AutoGen/Optionals/OptionalBeamPidLibrary.h"

FOptionalBeamPid UOptionalBeamPidLibrary::MakeOptional(FBeamPid Value)
{
	FOptionalBeamPid Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamPid UOptionalBeamPidLibrary::Conv_OptionalFromValue(FBeamPid Value)
{
	FOptionalBeamPid Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamPidLibrary::HasValue(const FOptionalBeamPid& Optional, FBeamPid& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamPid UOptionalBeamPidLibrary::GetOptionalValue(const FOptionalBeamPid& Optional, FBeamPid DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

