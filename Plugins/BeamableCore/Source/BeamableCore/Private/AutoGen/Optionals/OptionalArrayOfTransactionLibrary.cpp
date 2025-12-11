

#include "AutoGen/Optionals/OptionalArrayOfTransactionLibrary.h"

FOptionalArrayOfTransaction UOptionalArrayOfTransactionLibrary::MakeOptional(TArray<UTransaction*> Value)
{
	FOptionalArrayOfTransaction Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfTransaction UOptionalArrayOfTransactionLibrary::Conv_OptionalFromValue(TArray<UTransaction*> Value)
{
	FOptionalArrayOfTransaction Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfTransactionLibrary::HasValue(const FOptionalArrayOfTransaction& Optional, TArray<UTransaction*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UTransaction*> UOptionalArrayOfTransactionLibrary::GetOptionalValue(const FOptionalArrayOfTransaction& Optional, TArray<UTransaction*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

