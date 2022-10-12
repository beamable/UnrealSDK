

#include "OptionalCatalogLibrary.h"

FOptionalCatalog UOptionalCatalogLibrary::MakeOptionalCatalog(UCatalog* Value)
{
	FOptionalCatalog Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalCatalog UOptionalCatalogLibrary::Conv_OptionalCatalogFromValue(UCatalog* Value)
{
	FOptionalCatalog Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

