
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2SupportedFederation.h"

FOptionalBeamoV2SupportedFederation::FOptionalBeamoV2SupportedFederation()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalBeamoV2SupportedFederation::FOptionalBeamoV2SupportedFederation(UBeamoV2SupportedFederation* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoV2SupportedFederation::GetAddr() const { return &Val; }

void FOptionalBeamoV2SupportedFederation::Set(const void* Data)
{
	Val = *((UBeamoV2SupportedFederation**)Data);
	IsSet = true;
}