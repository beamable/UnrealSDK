

#include "AutoGen/Optionals/OptionalInventoryFiltersDTOLibrary.h"

FOptionalInventoryFiltersDTO UOptionalInventoryFiltersDTOLibrary::MakeOptional(UInventoryFiltersDTO* Value)
{
	FOptionalInventoryFiltersDTO Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalInventoryFiltersDTO UOptionalInventoryFiltersDTOLibrary::Conv_OptionalFromValue(UInventoryFiltersDTO* Value)
{
	FOptionalInventoryFiltersDTO Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalInventoryFiltersDTOLibrary::HasValue(const FOptionalInventoryFiltersDTO& Optional, UInventoryFiltersDTO*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UInventoryFiltersDTO* UOptionalInventoryFiltersDTOLibrary::GetOptionalValue(const FOptionalInventoryFiltersDTO& Optional, UInventoryFiltersDTO* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

