

#include "OptionalArrayOfObjectRequestBodyLibrary.h"

FOptionalArrayOfObjectRequestBody UOptionalArrayOfObjectRequestBodyLibrary::MakeOptionalArrayOfObjectRequestBody(TArray<UObjectRequestBody*> Value)
{
	FOptionalArrayOfObjectRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfObjectRequestBody UOptionalArrayOfObjectRequestBodyLibrary::Conv_OptionalArrayOfObjectRequestBodyFromValue(TArray<UObjectRequestBody*> Value)
{
	FOptionalArrayOfObjectRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

