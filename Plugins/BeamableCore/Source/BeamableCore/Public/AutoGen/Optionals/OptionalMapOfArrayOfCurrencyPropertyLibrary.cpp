

#include "OptionalMapOfArrayOfCurrencyPropertyLibrary.h"

FOptionalMapOfArrayOfCurrencyProperty UOptionalMapOfArrayOfCurrencyPropertyLibrary::MakeOptionalMapOfArrayOfCurrencyProperty(TMap<FString, FArrayOfCurrencyProperty> Value)
{
	FOptionalMapOfArrayOfCurrencyProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfArrayOfCurrencyProperty UOptionalMapOfArrayOfCurrencyPropertyLibrary::Conv_OptionalMapOfArrayOfCurrencyPropertyFromValue(TMap<FString, FArrayOfCurrencyProperty> Value)
{
	FOptionalMapOfArrayOfCurrencyProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

