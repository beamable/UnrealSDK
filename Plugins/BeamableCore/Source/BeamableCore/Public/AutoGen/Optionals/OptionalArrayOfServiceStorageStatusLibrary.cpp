

#include "OptionalArrayOfServiceStorageStatusLibrary.h"

FOptionalArrayOfServiceStorageStatus UOptionalArrayOfServiceStorageStatusLibrary::MakeOptionalArrayOfServiceStorageStatus(TArray<UServiceStorageStatus*> Value)
{
	FOptionalArrayOfServiceStorageStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceStorageStatus UOptionalArrayOfServiceStorageStatusLibrary::Conv_OptionalArrayOfServiceStorageStatusFromValue(TArray<UServiceStorageStatus*> Value)
{
	FOptionalArrayOfServiceStorageStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

