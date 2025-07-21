
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceStorageReference.h"

FOptionalArrayOfBeamoV2ServiceStorageReference::FOptionalArrayOfBeamoV2ServiceStorageReference()
{
	Val = TArray<UBeamoV2ServiceStorageReference*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2ServiceStorageReference::FOptionalArrayOfBeamoV2ServiceStorageReference(TArray<UBeamoV2ServiceStorageReference*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2ServiceStorageReference::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2ServiceStorageReference::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2ServiceStorageReference*>*)Data);
	IsSet = true;
}