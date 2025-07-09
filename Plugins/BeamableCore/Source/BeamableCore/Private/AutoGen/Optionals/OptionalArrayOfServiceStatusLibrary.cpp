

#include "AutoGen/Optionals/OptionalArrayOfServiceStatusLibrary.h"

FOptionalArrayOfServiceStatus UOptionalArrayOfServiceStatusLibrary::MakeOptional(TArray<UServiceStatus*> Value)
{
	FOptionalArrayOfServiceStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceStatus UOptionalArrayOfServiceStatusLibrary::Conv_OptionalFromValue(TArray<UServiceStatus*> Value)
{
	FOptionalArrayOfServiceStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfServiceStatusLibrary::HasValue(const FOptionalArrayOfServiceStatus& Optional, TArray<UServiceStatus*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UServiceStatus*> UOptionalArrayOfServiceStatusLibrary::GetOptionalValue(const FOptionalArrayOfServiceStatus& Optional, TArray<UServiceStatus*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

