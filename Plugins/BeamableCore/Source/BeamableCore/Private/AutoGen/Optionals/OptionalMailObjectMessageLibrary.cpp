

#include "AutoGen/Optionals/OptionalMailObjectMessageLibrary.h"

FOptionalMailObjectMessage UOptionalMailObjectMessageLibrary::MakeOptional(UMailObjectMessage* Value)
{
	FOptionalMailObjectMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMailObjectMessage UOptionalMailObjectMessageLibrary::Conv_OptionalFromValue(UMailObjectMessage* Value)
{
	FOptionalMailObjectMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMailObjectMessageLibrary::HasValue(const FOptionalMailObjectMessage& Optional, UMailObjectMessage*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UMailObjectMessage* UOptionalMailObjectMessageLibrary::GetOptionalValue(const FOptionalMailObjectMessage& Optional, UMailObjectMessage* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

