

#include "AutoGen/Optionals/OptionalObjectIdLibrary.h"

FOptionalObjectId UOptionalObjectIdLibrary::MakeOptional(UObjectId* Value)
{
	FOptionalObjectId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalObjectId UOptionalObjectIdLibrary::Conv_OptionalFromValue(UObjectId* Value)
{
	FOptionalObjectId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalObjectIdLibrary::HasValue(const FOptionalObjectId& Optional, UObjectId*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UObjectId* UOptionalObjectIdLibrary::GetOptionalValue(const FOptionalObjectId& Optional, UObjectId* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

