

#include "AutoGen/Optionals/OptionalArrayOfBeamGamerTagLibrary.h"

FOptionalArrayOfBeamGamerTag UOptionalArrayOfBeamGamerTagLibrary::MakeOptional(TArray<FBeamGamerTag> Value)
{
	FOptionalArrayOfBeamGamerTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamGamerTag UOptionalArrayOfBeamGamerTagLibrary::Conv_OptionalFromValue(TArray<FBeamGamerTag> Value)
{
	FOptionalArrayOfBeamGamerTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamGamerTagLibrary::HasValue(const FOptionalArrayOfBeamGamerTag& Optional, TArray<FBeamGamerTag>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<FBeamGamerTag> UOptionalArrayOfBeamGamerTagLibrary::GetOptionalValue(const FOptionalArrayOfBeamGamerTag& Optional, TArray<FBeamGamerTag> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

