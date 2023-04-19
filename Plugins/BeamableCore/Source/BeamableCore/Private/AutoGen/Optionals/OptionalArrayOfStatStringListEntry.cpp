
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfStatStringListEntry.h"

FOptionalArrayOfStatStringListEntry::FOptionalArrayOfStatStringListEntry()
{
	Val = TArray<UStatStringListEntry*>();
	IsSet = false;
}

FOptionalArrayOfStatStringListEntry::FOptionalArrayOfStatStringListEntry(TArray<UStatStringListEntry*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfStatStringListEntry::GetAddr() const { return &Val; }

void FOptionalArrayOfStatStringListEntry::Set(const void* Data)
{
	Val = *((TArray<UStatStringListEntry*>*)Data);
	IsSet = true;
}