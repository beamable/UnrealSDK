

#include "AutoGen/Optionals/OptionalArrayOfPropertyFilterDTOLibrary.h"

FOptionalArrayOfPropertyFilterDTO UOptionalArrayOfPropertyFilterDTOLibrary::MakeOptional(TArray<UPropertyFilterDTO*> Value)
{
	FOptionalArrayOfPropertyFilterDTO Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfPropertyFilterDTO UOptionalArrayOfPropertyFilterDTOLibrary::Conv_OptionalFromValue(TArray<UPropertyFilterDTO*> Value)
{
	FOptionalArrayOfPropertyFilterDTO Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfPropertyFilterDTOLibrary::HasValue(const FOptionalArrayOfPropertyFilterDTO& Optional, TArray<UPropertyFilterDTO*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UPropertyFilterDTO*> UOptionalArrayOfPropertyFilterDTOLibrary::GetOptionalValue(const FOptionalArrayOfPropertyFilterDTO& Optional, TArray<UPropertyFilterDTO*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

