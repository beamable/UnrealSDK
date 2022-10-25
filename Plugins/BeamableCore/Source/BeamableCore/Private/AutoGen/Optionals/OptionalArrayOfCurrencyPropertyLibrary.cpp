

#include "AutoGen/Optionals/OptionalArrayOfCurrencyPropertyLibrary.h"

FOptionalArrayOfCurrencyProperty UOptionalArrayOfCurrencyPropertyLibrary::MakeOptional(TArray<UCurrencyProperty*> Value)
{
	FOptionalArrayOfCurrencyProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCurrencyProperty UOptionalArrayOfCurrencyPropertyLibrary::Conv_OptionalFromValue(TArray<UCurrencyProperty*> Value)
{
	FOptionalArrayOfCurrencyProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfCurrencyPropertyLibrary::HasValue(const FOptionalArrayOfCurrencyProperty& Optional, TArray<UCurrencyProperty*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UCurrencyProperty*> UOptionalArrayOfCurrencyPropertyLibrary::GetOptionalValue(const FOptionalArrayOfCurrencyProperty& Optional, TArray<UCurrencyProperty*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

