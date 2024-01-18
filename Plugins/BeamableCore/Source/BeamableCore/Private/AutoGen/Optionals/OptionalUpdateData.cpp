
#include "BeamableCore/Public/AutoGen/Optionals/OptionalUpdateData.h"

FOptionalUpdateData::FOptionalUpdateData()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalUpdateData::FOptionalUpdateData(UUpdateData* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalUpdateData::GetAddr() const { return &Val; }

void FOptionalUpdateData::Set(const void* Data)
{
	Val = *((UUpdateData**)Data);
	IsSet = true;
}