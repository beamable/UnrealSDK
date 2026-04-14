
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceLoggingContext.h"

FOptionalArrayOfBeamoV2ServiceLoggingContext::FOptionalArrayOfBeamoV2ServiceLoggingContext()
{
	Val = TArray<UBeamoV2ServiceLoggingContext*>();
	IsSet = false;
}

FOptionalArrayOfBeamoV2ServiceLoggingContext::FOptionalArrayOfBeamoV2ServiceLoggingContext(TArray<UBeamoV2ServiceLoggingContext*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamoV2ServiceLoggingContext::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamoV2ServiceLoggingContext::Set(const void* Data)
{
	Val = *((TArray<UBeamoV2ServiceLoggingContext*>*)Data);
	IsSet = true;
}