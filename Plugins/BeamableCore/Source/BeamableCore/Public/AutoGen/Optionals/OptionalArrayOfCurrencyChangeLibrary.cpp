

#include "OptionalArrayOfCurrencyChangeLibrary.h"

FOptionalArrayOfCurrencyChange UOptionalArrayOfCurrencyChangeLibrary::MakeOptionalArrayOfCurrencyChange(TArray<UCurrencyChange*> Value)
{
	FOptionalArrayOfCurrencyChange Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCurrencyChange UOptionalArrayOfCurrencyChangeLibrary::Conv_OptionalArrayOfCurrencyChangeFromValue(TArray<UCurrencyChange*> Value)
{
	FOptionalArrayOfCurrencyChange Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

