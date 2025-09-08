

#include "AutoGen/Optionals/OptionalArrayOfAccountsBasicInFlightMessageLibrary.h"

FOptionalArrayOfAccountsBasicInFlightMessage UOptionalArrayOfAccountsBasicInFlightMessageLibrary::MakeOptional(TArray<UAccountsBasicInFlightMessage*> Value)
{
	FOptionalArrayOfAccountsBasicInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAccountsBasicInFlightMessage UOptionalArrayOfAccountsBasicInFlightMessageLibrary::Conv_OptionalFromValue(TArray<UAccountsBasicInFlightMessage*> Value)
{
	FOptionalArrayOfAccountsBasicInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfAccountsBasicInFlightMessageLibrary::HasValue(const FOptionalArrayOfAccountsBasicInFlightMessage& Optional, TArray<UAccountsBasicInFlightMessage*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UAccountsBasicInFlightMessage*> UOptionalArrayOfAccountsBasicInFlightMessageLibrary::GetOptionalValue(const FOptionalArrayOfAccountsBasicInFlightMessage& Optional, TArray<UAccountsBasicInFlightMessage*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

