

#include "AutoGen/Optionals/OptionalArrayOfCurrencyChangeLibrary.h"

FOptionalArrayOfCurrencyChange UOptionalArrayOfCurrencyChangeLibrary::MakeOptional(TArray<UCurrencyChange*> Value)
{
	FOptionalArrayOfCurrencyChange Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCurrencyChange UOptionalArrayOfCurrencyChangeLibrary::Conv_OptionalFromValue(TArray<UCurrencyChange*> Value)
{
	FOptionalArrayOfCurrencyChange Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfCurrencyChangeLibrary::HasValue(const FOptionalArrayOfCurrencyChange& Optional, TArray<UCurrencyChange*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UCurrencyChange*> UOptionalArrayOfCurrencyChangeLibrary::GetOptionalValue(const FOptionalArrayOfCurrencyChange& Optional, TArray<UCurrencyChange*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

