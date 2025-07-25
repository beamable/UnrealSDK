
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceStorageStatus.h"

FOptionalArrayOfBeamoV2ServiceStorageStatus::FOptionalArrayOfBeamoV2ServiceStorageStatus()
{
	Val = TArray<UBeamoV2ServiceStorageStatus*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2ServiceStorageStatus::FOptionalArrayOfBeamoV2ServiceStorageStatus(TArray<UBeamoV2ServiceStorageStatus*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2ServiceStorageStatus::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2ServiceStorageStatus::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2ServiceStorageStatus*>*)Data);
	IsSet = true;
}