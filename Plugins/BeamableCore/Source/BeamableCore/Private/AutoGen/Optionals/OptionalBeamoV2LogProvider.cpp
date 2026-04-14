
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2LogProvider.h"

FOptionalBeamoV2LogProvider::FOptionalBeamoV2LogProvider()
{
	Val = EBeamBeamoV2LogProvider();
	IsSet = false;
}

FOptionalBeamoV2LogProvider::FOptionalBeamoV2LogProvider(EBeamBeamoV2LogProvider Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoV2LogProvider::GetAddr() const { return &Val; }

void FOptionalBeamoV2LogProvider::Set(const void* Data)
{
	Val = *((EBeamBeamoV2LogProvider*)Data);
	IsSet = true;
}