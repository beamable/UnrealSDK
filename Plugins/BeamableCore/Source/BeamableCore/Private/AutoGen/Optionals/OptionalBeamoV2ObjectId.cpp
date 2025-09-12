
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2ObjectId.h"

FOptionalBeamoV2ObjectId::FOptionalBeamoV2ObjectId()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalBeamoV2ObjectId::FOptionalBeamoV2ObjectId(UBeamoV2ObjectId* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoV2ObjectId::GetAddr() const { return &Val; }

void FOptionalBeamoV2ObjectId::Set(const void* Data)
{
	Val = *((UBeamoV2ObjectId**)Data);
	IsSet = true;
}