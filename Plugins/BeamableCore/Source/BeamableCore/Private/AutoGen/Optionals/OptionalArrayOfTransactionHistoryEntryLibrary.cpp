

#include "AutoGen/Optionals/OptionalArrayOfTransactionHistoryEntryLibrary.h"

FOptionalArrayOfTransactionHistoryEntry UOptionalArrayOfTransactionHistoryEntryLibrary::MakeOptional(TArray<UTransactionHistoryEntry*> Value)
{
	FOptionalArrayOfTransactionHistoryEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfTransactionHistoryEntry UOptionalArrayOfTransactionHistoryEntryLibrary::Conv_OptionalFromValue(TArray<UTransactionHistoryEntry*> Value)
{
	FOptionalArrayOfTransactionHistoryEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfTransactionHistoryEntryLibrary::HasValue(const FOptionalArrayOfTransactionHistoryEntry& Optional, TArray<UTransactionHistoryEntry*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UTransactionHistoryEntry*> UOptionalArrayOfTransactionHistoryEntryLibrary::GetOptionalValue(const FOptionalArrayOfTransactionHistoryEntry& Optional, TArray<UTransactionHistoryEntry*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

