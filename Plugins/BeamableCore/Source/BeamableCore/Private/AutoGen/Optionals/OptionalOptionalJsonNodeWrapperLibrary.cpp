

#include "AutoGen/Optionals/OptionalOptionalJsonNodeWrapperLibrary.h"

FOptionalOptionalJsonNodeWrapper UOptionalOptionalJsonNodeWrapperLibrary::MakeOptional(UOptionalJsonNodeWrapper* Value)
{
	FOptionalOptionalJsonNodeWrapper Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalOptionalJsonNodeWrapper UOptionalOptionalJsonNodeWrapperLibrary::Conv_OptionalFromValue(UOptionalJsonNodeWrapper* Value)
{
	FOptionalOptionalJsonNodeWrapper Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalOptionalJsonNodeWrapperLibrary::HasValue(const FOptionalOptionalJsonNodeWrapper& Optional, UOptionalJsonNodeWrapper*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UOptionalJsonNodeWrapper* UOptionalOptionalJsonNodeWrapperLibrary::GetOptionalValue(const FOptionalOptionalJsonNodeWrapper& Optional, UOptionalJsonNodeWrapper* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

