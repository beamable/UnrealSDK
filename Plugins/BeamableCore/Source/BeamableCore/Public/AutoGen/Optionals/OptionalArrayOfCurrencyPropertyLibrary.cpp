

#include "OptionalArrayOfCurrencyPropertyLibrary.h"

FOptionalArrayOfCurrencyProperty UOptionalArrayOfCurrencyPropertyLibrary::MakeOptionalArrayOfCurrencyProperty(TArray<UCurrencyProperty*> Value)
{
	FOptionalArrayOfCurrencyProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCurrencyProperty UOptionalArrayOfCurrencyPropertyLibrary::Conv_OptionalArrayOfCurrencyPropertyFromValue(TArray<UCurrencyProperty*> Value)
{
	FOptionalArrayOfCurrencyProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

