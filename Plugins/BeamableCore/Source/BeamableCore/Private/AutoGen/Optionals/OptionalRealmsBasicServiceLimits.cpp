
#include "BeamableCore/Public/AutoGen/Optionals/OptionalRealmsBasicServiceLimits.h"

FOptionalRealmsBasicServiceLimits::FOptionalRealmsBasicServiceLimits()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalRealmsBasicServiceLimits::FOptionalRealmsBasicServiceLimits(URealmsBasicServiceLimits* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalRealmsBasicServiceLimits::GetAddr() const { return &Val; }

void FOptionalRealmsBasicServiceLimits::Set(const void* Data)
{
	Val = *((URealmsBasicServiceLimits**)Data);
	IsSet = true;
}