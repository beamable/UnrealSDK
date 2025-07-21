
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2SupportedFederation.h"

FOptionalArrayOfBeamoV2SupportedFederation::FOptionalArrayOfBeamoV2SupportedFederation()
{
	Val = TArray<UBeamoV2SupportedFederation*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2SupportedFederation::FOptionalArrayOfBeamoV2SupportedFederation(TArray<UBeamoV2SupportedFederation*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2SupportedFederation::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2SupportedFederation::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2SupportedFederation*>*)Data);
	IsSet = true;
}