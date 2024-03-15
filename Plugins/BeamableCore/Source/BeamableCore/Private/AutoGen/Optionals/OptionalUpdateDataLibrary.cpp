

#include "AutoGen/Optionals/OptionalUpdateDataLibrary.h"

FOptionalUpdateData UOptionalUpdateDataLibrary::MakeOptional(UUpdateData* Value)
{
	FOptionalUpdateData Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalUpdateData UOptionalUpdateDataLibrary::Conv_OptionalFromValue(UUpdateData* Value)
{
	FOptionalUpdateData Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalUpdateDataLibrary::HasValue(const FOptionalUpdateData& Optional, UUpdateData*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UUpdateData* UOptionalUpdateDataLibrary::GetOptionalValue(const FOptionalUpdateData& Optional, UUpdateData* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

