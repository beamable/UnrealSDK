

#include "AutoGen/Optionals/OptionalTokenResponseLibrary.h"

FOptionalTokenResponse UOptionalTokenResponseLibrary::MakeOptional(UTokenResponse* Value)
{
	FOptionalTokenResponse Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalTokenResponse UOptionalTokenResponseLibrary::Conv_OptionalFromValue(UTokenResponse* Value)
{
	FOptionalTokenResponse Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalTokenResponseLibrary::HasValue(const FOptionalTokenResponse& Optional, UTokenResponse*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UTokenResponse* UOptionalTokenResponseLibrary::GetOptionalValue(const FOptionalTokenResponse& Optional, UTokenResponse* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

