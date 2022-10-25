

#include "AutoGen/Optionals/OptionalArrayOfGroupRoleLibrary.h"

FOptionalArrayOfGroupRole UOptionalArrayOfGroupRoleLibrary::MakeOptional(TArray<UGroupRole*> Value)
{
	FOptionalArrayOfGroupRole Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfGroupRole UOptionalArrayOfGroupRoleLibrary::Conv_OptionalFromValue(TArray<UGroupRole*> Value)
{
	FOptionalArrayOfGroupRole Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfGroupRoleLibrary::HasValue(const FOptionalArrayOfGroupRole& Optional, TArray<UGroupRole*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UGroupRole*> UOptionalArrayOfGroupRoleLibrary::GetOptionalValue(const FOptionalArrayOfGroupRole& Optional, TArray<UGroupRole*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

