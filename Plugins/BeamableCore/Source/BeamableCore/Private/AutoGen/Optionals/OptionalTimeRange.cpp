
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTimeRange.h"

FOptionalTimeRange::FOptionalTimeRange()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalTimeRange::FOptionalTimeRange(UTimeRange* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalTimeRange::GetAddr() const { return &Val; }

void FOptionalTimeRange::Set(const void* Data)
{
	Val = *((UTimeRange**)Data);
	IsSet = true;
}