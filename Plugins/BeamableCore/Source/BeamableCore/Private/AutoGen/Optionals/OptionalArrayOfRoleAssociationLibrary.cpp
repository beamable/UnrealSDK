

#include "AutoGen/Optionals/OptionalArrayOfRoleAssociationLibrary.h"

FOptionalArrayOfRoleAssociation UOptionalArrayOfRoleAssociationLibrary::MakeOptional(TArray<URoleAssociation*> Value)
{
	FOptionalArrayOfRoleAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRoleAssociation UOptionalArrayOfRoleAssociationLibrary::Conv_OptionalFromValue(TArray<URoleAssociation*> Value)
{
	FOptionalArrayOfRoleAssociation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfRoleAssociationLibrary::HasValue(const FOptionalArrayOfRoleAssociation& Optional, TArray<URoleAssociation*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<URoleAssociation*> UOptionalArrayOfRoleAssociationLibrary::GetOptionalValue(const FOptionalArrayOfRoleAssociation& Optional, TArray<URoleAssociation*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

