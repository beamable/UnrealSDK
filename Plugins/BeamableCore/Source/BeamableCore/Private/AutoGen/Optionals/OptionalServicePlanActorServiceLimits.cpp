
#include "BeamableCore/Public/AutoGen/Optionals/OptionalServicePlanActorServiceLimits.h"

FOptionalServicePlanActorServiceLimits::FOptionalServicePlanActorServiceLimits()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalServicePlanActorServiceLimits::FOptionalServicePlanActorServiceLimits(UServicePlanActorServiceLimits* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalServicePlanActorServiceLimits::GetAddr() const { return &Val; }

void FOptionalServicePlanActorServiceLimits::Set(const void* Data)
{
	Val = *((UServicePlanActorServiceLimits**)Data);
	IsSet = true;
}