

#include "AutoGen/Optionals/OptionalArrayOfItemUpdateRequestBodyLibrary.h"

FOptionalArrayOfItemUpdateRequestBody UOptionalArrayOfItemUpdateRequestBodyLibrary::MakeOptional(TArray<UItemUpdateRequestBody*> Value)
{
	FOptionalArrayOfItemUpdateRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfItemUpdateRequestBody UOptionalArrayOfItemUpdateRequestBodyLibrary::Conv_OptionalFromValue(TArray<UItemUpdateRequestBody*> Value)
{
	FOptionalArrayOfItemUpdateRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfItemUpdateRequestBodyLibrary::HasValue(const FOptionalArrayOfItemUpdateRequestBody& Optional, TArray<UItemUpdateRequestBody*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UItemUpdateRequestBody*> UOptionalArrayOfItemUpdateRequestBodyLibrary::GetOptionalValue(const FOptionalArrayOfItemUpdateRequestBody& Optional, TArray<UItemUpdateRequestBody*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

