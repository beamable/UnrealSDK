

#include "OptionalArrayOfRoleMappingLibrary.h"

FOptionalArrayOfRoleMapping UOptionalArrayOfRoleMappingLibrary::MakeOptionalArrayOfRoleMapping(TArray<URoleMapping*> Value)
{
	FOptionalArrayOfRoleMapping Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRoleMapping UOptionalArrayOfRoleMappingLibrary::Conv_OptionalArrayOfRoleMappingFromValue(TArray<URoleMapping*> Value)
{
	FOptionalArrayOfRoleMapping Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

