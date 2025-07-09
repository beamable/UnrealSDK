
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoActorServiceReference.h"

FOptionalArrayOfBeamoActorServiceReference::FOptionalArrayOfBeamoActorServiceReference()
{
	Val = TArray<UBeamoActorServiceReference*>();
	IsSet = false;
}

FOptionalArrayOfBeamoActorServiceReference::FOptionalArrayOfBeamoActorServiceReference(TArray<UBeamoActorServiceReference*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoActorServiceReference::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoActorServiceReference::Set(const void* Data)
{
	Val = *((TArray<UBeamoActorServiceReference*>*)Data);
	IsSet = true;
}