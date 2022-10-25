

#include "AutoGen/Optionals/OptionalArrayOfItemCreateRequestBodyLibrary.h"

FOptionalArrayOfItemCreateRequestBody UOptionalArrayOfItemCreateRequestBodyLibrary::MakeOptional(TArray<UItemCreateRequestBody*> Value)
{
	FOptionalArrayOfItemCreateRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfItemCreateRequestBody UOptionalArrayOfItemCreateRequestBodyLibrary::Conv_OptionalFromValue(TArray<UItemCreateRequestBody*> Value)
{
	FOptionalArrayOfItemCreateRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfItemCreateRequestBodyLibrary::HasValue(const FOptionalArrayOfItemCreateRequestBody& Optional, TArray<UItemCreateRequestBody*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UItemCreateRequestBody*> UOptionalArrayOfItemCreateRequestBodyLibrary::GetOptionalValue(const FOptionalArrayOfItemCreateRequestBody& Optional, TArray<UItemCreateRequestBody*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

