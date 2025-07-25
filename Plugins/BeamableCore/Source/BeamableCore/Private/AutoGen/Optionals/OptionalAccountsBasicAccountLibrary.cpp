

#include "AutoGen/Optionals/OptionalAccountsBasicAccountLibrary.h"

FOptionalAccountsBasicAccount UOptionalAccountsBasicAccountLibrary::MakeOptional(UAccountsBasicAccount* Value)
{
	FOptionalAccountsBasicAccount Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalAccountsBasicAccount UOptionalAccountsBasicAccountLibrary::Conv_OptionalFromValue(UAccountsBasicAccount* Value)
{
	FOptionalAccountsBasicAccount Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalAccountsBasicAccountLibrary::HasValue(const FOptionalAccountsBasicAccount& Optional, UAccountsBasicAccount*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UAccountsBasicAccount* UOptionalAccountsBasicAccountLibrary::GetOptionalValue(const FOptionalAccountsBasicAccount& Optional, UAccountsBasicAccount* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

