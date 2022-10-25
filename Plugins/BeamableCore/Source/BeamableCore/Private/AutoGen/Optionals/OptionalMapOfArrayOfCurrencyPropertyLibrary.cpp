

#include "AutoGen/Optionals/OptionalMapOfArrayOfCurrencyPropertyLibrary.h"

FOptionalMapOfArrayOfCurrencyProperty UOptionalMapOfArrayOfCurrencyPropertyLibrary::MakeOptional(TMap<FString, FArrayOfCurrencyProperty> Value)
{
	FOptionalMapOfArrayOfCurrencyProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfArrayOfCurrencyProperty UOptionalMapOfArrayOfCurrencyPropertyLibrary::Conv_OptionalFromValue(TMap<FString, FArrayOfCurrencyProperty> Value)
{
	FOptionalMapOfArrayOfCurrencyProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMapOfArrayOfCurrencyPropertyLibrary::HasValue(const FOptionalMapOfArrayOfCurrencyProperty& Optional, TMap<FString, FArrayOfCurrencyProperty>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TMap<FString, FArrayOfCurrencyProperty> UOptionalMapOfArrayOfCurrencyPropertyLibrary::GetOptionalValue(const FOptionalMapOfArrayOfCurrencyProperty& Optional, TMap<FString, FArrayOfCurrencyProperty> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

