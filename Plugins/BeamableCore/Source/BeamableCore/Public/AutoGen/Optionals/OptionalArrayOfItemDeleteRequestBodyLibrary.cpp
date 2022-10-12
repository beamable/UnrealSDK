

#include "OptionalArrayOfItemDeleteRequestBodyLibrary.h"

FOptionalArrayOfItemDeleteRequestBody UOptionalArrayOfItemDeleteRequestBodyLibrary::MakeOptionalArrayOfItemDeleteRequestBody(TArray<UItemDeleteRequestBody*> Value)
{
	FOptionalArrayOfItemDeleteRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfItemDeleteRequestBody UOptionalArrayOfItemDeleteRequestBodyLibrary::Conv_OptionalArrayOfItemDeleteRequestBodyFromValue(TArray<UItemDeleteRequestBody*> Value)
{
	FOptionalArrayOfItemDeleteRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

