
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2OrderDirection.h"

FOptionalBeamoV2OrderDirection::FOptionalBeamoV2OrderDirection()
{
	Val = EBeamBeamoV2OrderDirection();
	IsSet = false;
}

FOptionalBeamoV2OrderDirection::FOptionalBeamoV2OrderDirection(EBeamBeamoV2OrderDirection Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoV2OrderDirection::GetAddr() const { return &Val; }

void FOptionalBeamoV2OrderDirection::Set(const void* Data)
{
	Val = *((EBeamBeamoV2OrderDirection*)Data);
	IsSet = true;
}