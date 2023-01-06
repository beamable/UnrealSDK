

#include "AutoGen/Optionals/OptionalArrayOfBeamPidLibrary.h"

FOptionalArrayOfBeamPid UOptionalArrayOfBeamPidLibrary::MakeOptional(TArray<FBeamPid> Value)
{
	FOptionalArrayOfBeamPid Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamPid UOptionalArrayOfBeamPidLibrary::Conv_OptionalFromValue(TArray<FBeamPid> Value)
{
	FOptionalArrayOfBeamPid Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamPidLibrary::HasValue(const FOptionalArrayOfBeamPid& Optional, TArray<FBeamPid>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<FBeamPid> UOptionalArrayOfBeamPidLibrary::GetOptionalValue(const FOptionalArrayOfBeamPid& Optional, TArray<FBeamPid> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

