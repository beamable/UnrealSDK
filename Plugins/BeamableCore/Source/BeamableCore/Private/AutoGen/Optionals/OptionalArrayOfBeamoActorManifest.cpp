
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoActorManifest.h"

FOptionalArrayOfBeamoActorManifest::FOptionalArrayOfBeamoActorManifest()
{
	Val = TArray<UBeamoActorManifest*>();
	IsSet = false;
}

FOptionalArrayOfBeamoActorManifest::FOptionalArrayOfBeamoActorManifest(TArray<UBeamoActorManifest*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoActorManifest::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoActorManifest::Set(const void* Data)
{
	Val = *((TArray<UBeamoActorManifest*>*)Data);
	IsSet = true;
}