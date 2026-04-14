
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSchedule.h"

FOptionalSchedule::FOptionalSchedule()
{
	Val = NewObject<USchedule>(GetTransientPackage());
	IsSet = false;
}

FOptionalSchedule::FOptionalSchedule(USchedule* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalSchedule::GetAddr() const { return &Val; }

void FOptionalSchedule::Set(const void* Data)
{
	Val = *((USchedule**)Data);
	IsSet = true;
}