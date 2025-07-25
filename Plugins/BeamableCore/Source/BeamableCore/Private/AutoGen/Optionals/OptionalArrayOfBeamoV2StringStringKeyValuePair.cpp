
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2StringStringKeyValuePair.h"

FOptionalArrayOfBeamoV2StringStringKeyValuePair::FOptionalArrayOfBeamoV2StringStringKeyValuePair()
{
	Val = TArray<UBeamoV2StringStringKeyValuePair*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2StringStringKeyValuePair::FOptionalArrayOfBeamoV2StringStringKeyValuePair(TArray<UBeamoV2StringStringKeyValuePair*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2StringStringKeyValuePair::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2StringStringKeyValuePair::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2StringStringKeyValuePair*>*)Data);
	IsSet = true;
}