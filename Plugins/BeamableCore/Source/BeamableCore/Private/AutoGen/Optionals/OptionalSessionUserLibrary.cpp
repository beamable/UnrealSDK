

#include "AutoGen/Optionals/OptionalSessionUserLibrary.h"

FOptionalSessionUser UOptionalSessionUserLibrary::MakeOptional(USessionUser* Value)
{
	FOptionalSessionUser Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalSessionUser UOptionalSessionUserLibrary::Conv_OptionalFromValue(USessionUser* Value)
{
	FOptionalSessionUser Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalSessionUserLibrary::HasValue(const FOptionalSessionUser& Optional, USessionUser*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

USessionUser* UOptionalSessionUserLibrary::GetOptionalValue(const FOptionalSessionUser& Optional, USessionUser* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

