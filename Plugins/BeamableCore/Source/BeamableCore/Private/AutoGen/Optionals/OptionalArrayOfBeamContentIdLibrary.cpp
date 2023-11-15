

#include "AutoGen/Optionals/OptionalArrayOfBeamContentIdLibrary.h"

FOptionalArrayOfBeamContentId UOptionalArrayOfBeamContentIdLibrary::MakeOptional(TArray<FBeamContentId> Value)
{
	FOptionalArrayOfBeamContentId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamContentId UOptionalArrayOfBeamContentIdLibrary::Conv_OptionalFromValue(TArray<FBeamContentId> Value)
{
	FOptionalArrayOfBeamContentId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamContentIdLibrary::HasValue(const FOptionalArrayOfBeamContentId& Optional, TArray<FBeamContentId>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<FBeamContentId> UOptionalArrayOfBeamContentIdLibrary::GetOptionalValue(const FOptionalArrayOfBeamContentId& Optional, TArray<FBeamContentId> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

