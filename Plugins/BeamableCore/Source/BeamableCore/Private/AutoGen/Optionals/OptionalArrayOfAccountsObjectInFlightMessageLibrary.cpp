

#include "AutoGen/Optionals/OptionalArrayOfAccountsObjectInFlightMessageLibrary.h"

FOptionalArrayOfAccountsObjectInFlightMessage UOptionalArrayOfAccountsObjectInFlightMessageLibrary::MakeOptional(TArray<UAccountsObjectInFlightMessage*> Value)
{
	FOptionalArrayOfAccountsObjectInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAccountsObjectInFlightMessage UOptionalArrayOfAccountsObjectInFlightMessageLibrary::Conv_OptionalFromValue(TArray<UAccountsObjectInFlightMessage*> Value)
{
	FOptionalArrayOfAccountsObjectInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfAccountsObjectInFlightMessageLibrary::HasValue(const FOptionalArrayOfAccountsObjectInFlightMessage& Optional, TArray<UAccountsObjectInFlightMessage*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UAccountsObjectInFlightMessage*> UOptionalArrayOfAccountsObjectInFlightMessageLibrary::GetOptionalValue(const FOptionalArrayOfAccountsObjectInFlightMessage& Optional, TArray<UAccountsObjectInFlightMessage*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

