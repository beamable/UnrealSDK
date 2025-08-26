
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2DatabaseMeasurement.h"

FOptionalArrayOfBeamoV2DatabaseMeasurement::FOptionalArrayOfBeamoV2DatabaseMeasurement()
{
	Val = TArray<UBeamoV2DatabaseMeasurement*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2DatabaseMeasurement::FOptionalArrayOfBeamoV2DatabaseMeasurement(TArray<UBeamoV2DatabaseMeasurement*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2DatabaseMeasurement::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2DatabaseMeasurement::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2DatabaseMeasurement*>*)Data);
	IsSet = true;
}