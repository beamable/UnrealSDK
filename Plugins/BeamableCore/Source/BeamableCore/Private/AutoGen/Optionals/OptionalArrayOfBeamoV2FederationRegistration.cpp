
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2FederationRegistration.h"

FOptionalArrayOfBeamoV2FederationRegistration::FOptionalArrayOfBeamoV2FederationRegistration()
{
	Val = TArray<UBeamoV2FederationRegistration*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2FederationRegistration::FOptionalArrayOfBeamoV2FederationRegistration(TArray<UBeamoV2FederationRegistration*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2FederationRegistration::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2FederationRegistration::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2FederationRegistration*>*)Data);
	IsSet = true;
}