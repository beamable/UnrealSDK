

#include "AutoGen/Optionals/OptionalArrayOfServiceStorageStatusLibrary.h"

FOptionalArrayOfServiceStorageStatus UOptionalArrayOfServiceStorageStatusLibrary::MakeOptional(TArray<UServiceStorageStatus*> Value)
{
	FOptionalArrayOfServiceStorageStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceStorageStatus UOptionalArrayOfServiceStorageStatusLibrary::Conv_OptionalFromValue(TArray<UServiceStorageStatus*> Value)
{
	FOptionalArrayOfServiceStorageStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfServiceStorageStatusLibrary::HasValue(const FOptionalArrayOfServiceStorageStatus& Optional, TArray<UServiceStorageStatus*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UServiceStorageStatus*> UOptionalArrayOfServiceStorageStatusLibrary::GetOptionalValue(const FOptionalArrayOfServiceStorageStatus& Optional, TArray<UServiceStorageStatus*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

