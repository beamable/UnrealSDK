
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoActorDataPoint.h"

FOptionalArrayOfBeamoActorDataPoint::FOptionalArrayOfBeamoActorDataPoint()
{
	Val = TArray<UBeamoActorDataPoint*>();
	IsSet = false;
}

FOptionalArrayOfBeamoActorDataPoint::FOptionalArrayOfBeamoActorDataPoint(TArray<UBeamoActorDataPoint*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoActorDataPoint::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoActorDataPoint::Set(const void* Data)
{
	Val = *((TArray<UBeamoActorDataPoint*>*)Data);
	IsSet = true;
}