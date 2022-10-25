

#include "AutoGen/Optionals/OptionalCatalogLibrary.h"

FOptionalCatalog UOptionalCatalogLibrary::MakeOptional(UCatalog* Value)
{
	FOptionalCatalog Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalCatalog UOptionalCatalogLibrary::Conv_OptionalFromValue(UCatalog* Value)
{
	FOptionalCatalog Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalCatalogLibrary::HasValue(const FOptionalCatalog& Optional, UCatalog*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UCatalog* UOptionalCatalogLibrary::GetOptionalValue(const FOptionalCatalog& Optional, UCatalog* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

