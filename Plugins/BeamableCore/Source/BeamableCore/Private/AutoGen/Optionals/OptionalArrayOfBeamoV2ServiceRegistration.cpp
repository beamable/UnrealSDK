
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceRegistration.h"

FOptionalArrayOfBeamoV2ServiceRegistration::FOptionalArrayOfBeamoV2ServiceRegistration()
{
	Val = TArray<UBeamoV2ServiceRegistration*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2ServiceRegistration::FOptionalArrayOfBeamoV2ServiceRegistration(TArray<UBeamoV2ServiceRegistration*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2ServiceRegistration::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2ServiceRegistration::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2ServiceRegistration*>*)Data);
	IsSet = true;
}