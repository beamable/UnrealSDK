
#include "BeamableCore/Public/AutoGen/Optionals/OptionalServiceLimits.h"

FOptionalServiceLimits::FOptionalServiceLimits()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalServiceLimits::FOptionalServiceLimits(UServiceLimits* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalServiceLimits::GetAddr() const { return &Val; }

void FOptionalServiceLimits::Set(const void* Data)
{
	Val = *((UServiceLimits**)Data);
	IsSet = true;
}