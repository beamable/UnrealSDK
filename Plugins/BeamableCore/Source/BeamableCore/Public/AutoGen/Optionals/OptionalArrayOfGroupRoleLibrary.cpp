

#include "OptionalArrayOfGroupRoleLibrary.h"

FOptionalArrayOfGroupRole UOptionalArrayOfGroupRoleLibrary::MakeOptionalArrayOfGroupRole(TArray<UGroupRole*> Value)
{
	FOptionalArrayOfGroupRole Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfGroupRole UOptionalArrayOfGroupRoleLibrary::Conv_OptionalArrayOfGroupRoleFromValue(TArray<UGroupRole*> Value)
{
	FOptionalArrayOfGroupRole Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

