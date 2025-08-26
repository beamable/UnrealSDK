
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceReference.h"

FOptionalArrayOfBeamoV2ServiceReference::FOptionalArrayOfBeamoV2ServiceReference()
{
	Val = TArray<UBeamoV2ServiceReference*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2ServiceReference::FOptionalArrayOfBeamoV2ServiceReference(TArray<UBeamoV2ServiceReference*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2ServiceReference::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2ServiceReference::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2ServiceReference*>*)Data);
	IsSet = true;
}