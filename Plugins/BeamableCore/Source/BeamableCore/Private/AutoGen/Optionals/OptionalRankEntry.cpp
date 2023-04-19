
#include "BeamableCore/Public/AutoGen/Optionals/OptionalRankEntry.h"

FOptionalRankEntry::FOptionalRankEntry()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalRankEntry::FOptionalRankEntry(URankEntry* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalRankEntry::GetAddr() const { return &Val; }

void FOptionalRankEntry::Set(const void* Data)
{
	Val = *((URankEntry**)Data);
	IsSet = true;
}