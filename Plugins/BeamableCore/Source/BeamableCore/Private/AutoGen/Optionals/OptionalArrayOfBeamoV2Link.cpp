
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2Link.h"

FOptionalArrayOfBeamoV2Link::FOptionalArrayOfBeamoV2Link()
{
	Val = TArray<UBeamoV2Link*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2Link::FOptionalArrayOfBeamoV2Link(TArray<UBeamoV2Link*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2Link::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2Link::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2Link*>*)Data);
	IsSet = true;
}