
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceComponent.h"

FOptionalArrayOfBeamoV2ServiceComponent::FOptionalArrayOfBeamoV2ServiceComponent()
{
	Val = TArray<UBeamoV2ServiceComponent*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2ServiceComponent::FOptionalArrayOfBeamoV2ServiceComponent(TArray<UBeamoV2ServiceComponent*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2ServiceComponent::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2ServiceComponent::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2ServiceComponent*>*)Data);
	IsSet = true;
}