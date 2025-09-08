

#include "AutoGen/Optionals/OptionalArrayOfGroupUsersObjectInFlightMessageLibrary.h"

FOptionalArrayOfGroupUsersObjectInFlightMessage UOptionalArrayOfGroupUsersObjectInFlightMessageLibrary::MakeOptional(TArray<UGroupUsersObjectInFlightMessage*> Value)
{
	FOptionalArrayOfGroupUsersObjectInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfGroupUsersObjectInFlightMessage UOptionalArrayOfGroupUsersObjectInFlightMessageLibrary::Conv_OptionalFromValue(TArray<UGroupUsersObjectInFlightMessage*> Value)
{
	FOptionalArrayOfGroupUsersObjectInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfGroupUsersObjectInFlightMessageLibrary::HasValue(const FOptionalArrayOfGroupUsersObjectInFlightMessage& Optional, TArray<UGroupUsersObjectInFlightMessage*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UGroupUsersObjectInFlightMessage*> UOptionalArrayOfGroupUsersObjectInFlightMessageLibrary::GetOptionalValue(const FOptionalArrayOfGroupUsersObjectInFlightMessage& Optional, TArray<UGroupUsersObjectInFlightMessage*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

