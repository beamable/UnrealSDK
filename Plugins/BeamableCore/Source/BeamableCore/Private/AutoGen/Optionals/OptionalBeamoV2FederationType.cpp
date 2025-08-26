
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2FederationType.h"

FOptionalBeamoV2FederationType::FOptionalBeamoV2FederationType()
{
	Val = EBeamBeamoV2FederationType();
	IsSet = false;
}

FOptionalBeamoV2FederationType::FOptionalBeamoV2FederationType(EBeamBeamoV2FederationType Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoV2FederationType::GetAddr() const { return &Val; }

void FOptionalBeamoV2FederationType::Set(const void* Data)
{
	Val = *((EBeamBeamoV2FederationType*)Data);
	IsSet = true;
}