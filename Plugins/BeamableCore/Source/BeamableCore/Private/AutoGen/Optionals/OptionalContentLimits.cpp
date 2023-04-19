
#include "BeamableCore/Public/AutoGen/Optionals/OptionalContentLimits.h"

FOptionalContentLimits::FOptionalContentLimits()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalContentLimits::FOptionalContentLimits(UContentLimits* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalContentLimits::GetAddr() const { return &Val; }

void FOptionalContentLimits::Set(const void* Data)
{
	Val = *((UContentLimits**)Data);
	IsSet = true;
}