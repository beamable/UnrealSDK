
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceStatus.h"

FOptionalArrayOfBeamoV2ServiceStatus::FOptionalArrayOfBeamoV2ServiceStatus()
{
	Val = TArray<UBeamoV2ServiceStatus*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2ServiceStatus::FOptionalArrayOfBeamoV2ServiceStatus(TArray<UBeamoV2ServiceStatus*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2ServiceStatus::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2ServiceStatus::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2ServiceStatus*>*)Data);
	IsSet = true;
}