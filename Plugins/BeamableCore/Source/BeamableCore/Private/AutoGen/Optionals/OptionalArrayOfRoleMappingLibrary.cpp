

#include "AutoGen/Optionals/OptionalArrayOfRoleMappingLibrary.h"

FOptionalArrayOfRoleMapping UOptionalArrayOfRoleMappingLibrary::MakeOptional(TArray<URoleMapping*> Value)
{
	FOptionalArrayOfRoleMapping Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRoleMapping UOptionalArrayOfRoleMappingLibrary::Conv_OptionalFromValue(TArray<URoleMapping*> Value)
{
	FOptionalArrayOfRoleMapping Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfRoleMappingLibrary::HasValue(const FOptionalArrayOfRoleMapping& Optional, TArray<URoleMapping*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<URoleMapping*> UOptionalArrayOfRoleMappingLibrary::GetOptionalValue(const FOptionalArrayOfRoleMapping& Optional, TArray<URoleMapping*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

