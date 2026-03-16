
#include "BeamableCore/Public/AutoGen/Optionals/OptionalRealmsBasicBeamoLimits.h"

FOptionalRealmsBasicBeamoLimits::FOptionalRealmsBasicBeamoLimits()
{
	Val = NewObject<URealmsBasicBeamoLimits>(GetTransientPackage());
	IsSet = false;
}

FOptionalRealmsBasicBeamoLimits::FOptionalRealmsBasicBeamoLimits(URealmsBasicBeamoLimits* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalRealmsBasicBeamoLimits::GetAddr() const { return &Val; }

void FOptionalRealmsBasicBeamoLimits::Set(const void* Data)
{
	Val = *((URealmsBasicBeamoLimits**)Data);
	IsSet = true;
}