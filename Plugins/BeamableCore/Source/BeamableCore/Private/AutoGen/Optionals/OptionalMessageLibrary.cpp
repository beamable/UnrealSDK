

#include "AutoGen/Optionals/OptionalMessageLibrary.h"

FOptionalMessage UOptionalMessageLibrary::MakeOptional(UMessage* Value)
{
	FOptionalMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMessage UOptionalMessageLibrary::Conv_OptionalFromValue(UMessage* Value)
{
	FOptionalMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMessageLibrary::HasValue(const FOptionalMessage& Optional, UMessage*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UMessage* UOptionalMessageLibrary::GetOptionalValue(const FOptionalMessage& Optional, UMessage* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

