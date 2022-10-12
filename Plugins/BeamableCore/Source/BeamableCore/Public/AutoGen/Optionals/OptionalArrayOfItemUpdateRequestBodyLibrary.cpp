

#include "OptionalArrayOfItemUpdateRequestBodyLibrary.h"

FOptionalArrayOfItemUpdateRequestBody UOptionalArrayOfItemUpdateRequestBodyLibrary::MakeOptionalArrayOfItemUpdateRequestBody(TArray<UItemUpdateRequestBody*> Value)
{
	FOptionalArrayOfItemUpdateRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfItemUpdateRequestBody UOptionalArrayOfItemUpdateRequestBodyLibrary::Conv_OptionalArrayOfItemUpdateRequestBodyFromValue(TArray<UItemUpdateRequestBody*> Value)
{
	FOptionalArrayOfItemUpdateRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

