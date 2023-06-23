

#include "AutoGen/Optionals/OptionalMatchTypeLibrary.h"

FOptionalMatchType UOptionalMatchTypeLibrary::MakeOptional(UMatchType* Value)
{
	FOptionalMatchType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMatchType UOptionalMatchTypeLibrary::Conv_OptionalFromValue(UMatchType* Value)
{
	FOptionalMatchType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMatchTypeLibrary::HasValue(const FOptionalMatchType& Optional, UMatchType*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UMatchType* UOptionalMatchTypeLibrary::GetOptionalValue(const FOptionalMatchType& Optional, UMatchType* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

