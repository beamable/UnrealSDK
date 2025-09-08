

#include "AutoGen/Optionals/OptionalArrayOfRealmAssociationLibrary.h"

FOptionalArrayOfRealmAssociation UOptionalArrayOfRealmAssociationLibrary::MakeOptional(TArray<URealmAssociation*> Value)
{
	FOptionalArrayOfRealmAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRealmAssociation UOptionalArrayOfRealmAssociationLibrary::Conv_OptionalFromValue(TArray<URealmAssociation*> Value)
{
	FOptionalArrayOfRealmAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfRealmAssociationLibrary::HasValue(const FOptionalArrayOfRealmAssociation& Optional, TArray<URealmAssociation*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<URealmAssociation*> UOptionalArrayOfRealmAssociationLibrary::GetOptionalValue(const FOptionalArrayOfRealmAssociation& Optional, TArray<URealmAssociation*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

