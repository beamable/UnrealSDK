
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2DataPoint.h"

FOptionalArrayOfBeamoV2DataPoint::FOptionalArrayOfBeamoV2DataPoint()
{
	Val = TArray<UBeamoV2DataPoint*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2DataPoint::FOptionalArrayOfBeamoV2DataPoint(TArray<UBeamoV2DataPoint*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2DataPoint::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2DataPoint::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2DataPoint*>*)Data);
	IsSet = true;
}