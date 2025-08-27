
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoLimits.h"

FOptionalBeamoLimits::FOptionalBeamoLimits()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalBeamoLimits::FOptionalBeamoLimits(UBeamoLimits* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoLimits::GetAddr() const { return &Val; }

void FOptionalBeamoLimits::Set(const void* Data)
{
	Val = *((UBeamoLimits**)Data);
	IsSet = true;
}