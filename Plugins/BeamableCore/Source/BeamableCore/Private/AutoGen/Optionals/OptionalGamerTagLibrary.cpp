

#include "AutoGen/Optionals/OptionalGamerTagLibrary.h"

FOptionalGamerTag UOptionalGamerTagLibrary::MakeOptional(UGamerTag* Value)
{
	FOptionalGamerTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalGamerTag UOptionalGamerTagLibrary::Conv_OptionalFromValue(UGamerTag* Value)
{
	FOptionalGamerTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalGamerTagLibrary::HasValue(const FOptionalGamerTag& Optional, UGamerTag*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UGamerTag* UOptionalGamerTagLibrary::GetOptionalValue(const FOptionalGamerTag& Optional, UGamerTag* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

