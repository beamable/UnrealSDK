
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPeriod.h"

FOptionalPeriod::FOptionalPeriod()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalPeriod::FOptionalPeriod(UPeriod* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalPeriod::GetAddr() const { return &Val; }

void FOptionalPeriod::Set(const void* Data)
{
	Val = *((UPeriod**)Data);
	IsSet = true;
}