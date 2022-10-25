

#include "AutoGen/Optionals/OptionalArrayOfObjectRequestBodyLibrary.h"

FOptionalArrayOfObjectRequestBody UOptionalArrayOfObjectRequestBodyLibrary::MakeOptional(TArray<UObjectRequestBody*> Value)
{
	FOptionalArrayOfObjectRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfObjectRequestBody UOptionalArrayOfObjectRequestBodyLibrary::Conv_OptionalFromValue(TArray<UObjectRequestBody*> Value)
{
	FOptionalArrayOfObjectRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfObjectRequestBodyLibrary::HasValue(const FOptionalArrayOfObjectRequestBody& Optional, TArray<UObjectRequestBody*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UObjectRequestBody*> UOptionalArrayOfObjectRequestBodyLibrary::GetOptionalValue(const FOptionalArrayOfObjectRequestBody& Optional, TArray<UObjectRequestBody*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

