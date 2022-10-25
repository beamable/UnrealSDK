

#include "AutoGen/Optionals/OptionalBoolLibrary.h"

FOptionalBool UOptionalBoolLibrary::MakeOptional(bool Value)
{
	FOptionalBool Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBool UOptionalBoolLibrary::Conv_OptionalFromValue(bool Value)
{
	FOptionalBool Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBoolLibrary::HasValue(const FOptionalBool& Optional, bool& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

bool UOptionalBoolLibrary::GetOptionalValue(const FOptionalBool& Optional, bool DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

