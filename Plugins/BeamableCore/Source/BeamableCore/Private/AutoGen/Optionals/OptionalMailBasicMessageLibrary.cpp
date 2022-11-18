

#include "AutoGen/Optionals/OptionalMailBasicMessageLibrary.h"

FOptionalMailBasicMessage UOptionalMailBasicMessageLibrary::MakeOptional(UMailBasicMessage* Value)
{
	FOptionalMailBasicMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMailBasicMessage UOptionalMailBasicMessageLibrary::Conv_OptionalFromValue(UMailBasicMessage* Value)
{
	FOptionalMailBasicMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMailBasicMessageLibrary::HasValue(const FOptionalMailBasicMessage& Optional, UMailBasicMessage*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UMailBasicMessage* UOptionalMailBasicMessageLibrary::GetOptionalValue(const FOptionalMailBasicMessage& Optional, UMailBasicMessage* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

