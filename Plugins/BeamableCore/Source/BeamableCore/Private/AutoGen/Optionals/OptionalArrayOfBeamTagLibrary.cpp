

#include "AutoGen/Optionals/OptionalArrayOfBeamTagLibrary.h"

FOptionalArrayOfBeamTag UOptionalArrayOfBeamTagLibrary::MakeOptional(TArray<FBeamTag> Value)
{
	FOptionalArrayOfBeamTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamTag UOptionalArrayOfBeamTagLibrary::Conv_OptionalFromValue(TArray<FBeamTag> Value)
{
	FOptionalArrayOfBeamTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamTagLibrary::HasValue(const FOptionalArrayOfBeamTag& Optional, TArray<FBeamTag>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<FBeamTag> UOptionalArrayOfBeamTagLibrary::GetOptionalValue(const FOptionalArrayOfBeamTag& Optional, TArray<FBeamTag> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

