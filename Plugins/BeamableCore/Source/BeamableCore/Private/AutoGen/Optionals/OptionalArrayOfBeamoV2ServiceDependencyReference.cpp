
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceDependencyReference.h"

FOptionalArrayOfBeamoV2ServiceDependencyReference::FOptionalArrayOfBeamoV2ServiceDependencyReference()
{
	Val = TArray<UBeamoV2ServiceDependencyReference*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2ServiceDependencyReference::FOptionalArrayOfBeamoV2ServiceDependencyReference(TArray<UBeamoV2ServiceDependencyReference*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2ServiceDependencyReference::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2ServiceDependencyReference::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2ServiceDependencyReference*>*)Data);
	IsSet = true;
}