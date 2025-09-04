
#include "BeamableCore/Public/AutoGen/Optionals/OptionalServicePlanActorBeamoLimits.h"

FOptionalServicePlanActorBeamoLimits::FOptionalServicePlanActorBeamoLimits()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalServicePlanActorBeamoLimits::FOptionalServicePlanActorBeamoLimits(UServicePlanActorBeamoLimits* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalServicePlanActorBeamoLimits::GetAddr() const { return &Val; }

void FOptionalServicePlanActorBeamoLimits::Set(const void* Data)
{
	Val = *((UServicePlanActorBeamoLimits**)Data);
	IsSet = true;
}