
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2LogContextRule.h"

FOptionalArrayOfBeamoV2LogContextRule::FOptionalArrayOfBeamoV2LogContextRule()
{
	Val = TArray<UBeamoV2LogContextRule*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2LogContextRule::FOptionalArrayOfBeamoV2LogContextRule(TArray<UBeamoV2LogContextRule*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2LogContextRule::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2LogContextRule::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2LogContextRule*>*)Data);
	IsSet = true;
}