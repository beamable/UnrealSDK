

#include "OptionalArrayOfItemCreateRequestBodyLibrary.h"

FOptionalArrayOfItemCreateRequestBody UOptionalArrayOfItemCreateRequestBodyLibrary::MakeOptionalArrayOfItemCreateRequestBody(TArray<UItemCreateRequestBody*> Value)
{
	FOptionalArrayOfItemCreateRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfItemCreateRequestBody UOptionalArrayOfItemCreateRequestBodyLibrary::Conv_OptionalArrayOfItemCreateRequestBodyFromValue(TArray<UItemCreateRequestBody*> Value)
{
	FOptionalArrayOfItemCreateRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

