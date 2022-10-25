

#include "AutoGen/Optionals/OptionalArrayOfServiceStorageReferenceLibrary.h"

FOptionalArrayOfServiceStorageReference UOptionalArrayOfServiceStorageReferenceLibrary::MakeOptional(TArray<UServiceStorageReference*> Value)
{
	FOptionalArrayOfServiceStorageReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceStorageReference UOptionalArrayOfServiceStorageReferenceLibrary::Conv_OptionalFromValue(TArray<UServiceStorageReference*> Value)
{
	FOptionalArrayOfServiceStorageReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfServiceStorageReferenceLibrary::HasValue(const FOptionalArrayOfServiceStorageReference& Optional, TArray<UServiceStorageReference*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UServiceStorageReference*> UOptionalArrayOfServiceStorageReferenceLibrary::GetOptionalValue(const FOptionalArrayOfServiceStorageReference& Optional, TArray<UServiceStorageReference*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

