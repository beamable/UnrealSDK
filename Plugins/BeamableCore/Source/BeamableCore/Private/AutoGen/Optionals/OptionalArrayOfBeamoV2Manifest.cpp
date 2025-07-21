
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2Manifest.h"

FOptionalArrayOfBeamoV2Manifest::FOptionalArrayOfBeamoV2Manifest()
{
	Val = TArray<UBeamoV2Manifest*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2Manifest::FOptionalArrayOfBeamoV2Manifest(TArray<UBeamoV2Manifest*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2Manifest::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2Manifest::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2Manifest*>*)Data);
	IsSet = true;
}