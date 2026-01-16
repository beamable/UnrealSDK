
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTransactionHistoryEntry.h"

FOptionalArrayOfTransactionHistoryEntry::FOptionalArrayOfTransactionHistoryEntry()
{
	Val = TArray<UTransactionHistoryEntry*>();
	IsSet = false;
}

FOptionalArrayOfTransactionHistoryEntry::FOptionalArrayOfTransactionHistoryEntry(TArray<UTransactionHistoryEntry*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfTransactionHistoryEntry::GetAddr() const { return &Val; }

void FOptionalArrayOfTransactionHistoryEntry::Set(const void* Data)
{
	Val = *((TArray<UTransactionHistoryEntry*>*)Data);
	IsSet = true;
}