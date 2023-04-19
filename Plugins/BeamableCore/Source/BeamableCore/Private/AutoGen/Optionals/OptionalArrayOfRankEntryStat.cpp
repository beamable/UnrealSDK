
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRankEntryStat.h"

FOptionalArrayOfRankEntryStat::FOptionalArrayOfRankEntryStat()
{
	Val = TArray<URankEntryStat*>();
	IsSet = false;
}

FOptionalArrayOfRankEntryStat::FOptionalArrayOfRankEntryStat(TArray<URankEntryStat*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfRankEntryStat::GetAddr() const { return &Val; }

void FOptionalArrayOfRankEntryStat::Set(const void* Data)
{
	Val = *((TArray<URankEntryStat*>*)Data);
	IsSet = true;
}