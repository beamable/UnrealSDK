

#include "OptionalArrayOfServiceStorageReferenceLibrary.h"

FOptionalArrayOfServiceStorageReference UOptionalArrayOfServiceStorageReferenceLibrary::MakeOptionalArrayOfServiceStorageReference(TArray<UServiceStorageReference*> Value)
{
	FOptionalArrayOfServiceStorageReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceStorageReference UOptionalArrayOfServiceStorageReferenceLibrary::Conv_OptionalArrayOfServiceStorageReferenceFromValue(TArray<UServiceStorageReference*> Value)
{
	FOptionalArrayOfServiceStorageReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

