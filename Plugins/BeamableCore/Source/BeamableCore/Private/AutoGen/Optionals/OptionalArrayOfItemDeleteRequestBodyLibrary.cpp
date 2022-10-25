

#include "AutoGen/Optionals/OptionalArrayOfItemDeleteRequestBodyLibrary.h"

FOptionalArrayOfItemDeleteRequestBody UOptionalArrayOfItemDeleteRequestBodyLibrary::MakeOptional(TArray<UItemDeleteRequestBody*> Value)
{
	FOptionalArrayOfItemDeleteRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfItemDeleteRequestBody UOptionalArrayOfItemDeleteRequestBodyLibrary::Conv_OptionalFromValue(TArray<UItemDeleteRequestBody*> Value)
{
	FOptionalArrayOfItemDeleteRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfItemDeleteRequestBodyLibrary::HasValue(const FOptionalArrayOfItemDeleteRequestBody& Optional, TArray<UItemDeleteRequestBody*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UItemDeleteRequestBody*> UOptionalArrayOfItemDeleteRequestBodyLibrary::GetOptionalValue(const FOptionalArrayOfItemDeleteRequestBody& Optional, TArray<UItemDeleteRequestBody*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

