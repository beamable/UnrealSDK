
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"

FOptionalInt32::FOptionalInt32()
{
	Val = int32();
	IsSet = false;
}

FOptionalInt32::FOptionalInt32(int32 Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalInt32::GetAddr() const { return &Val; }

void FOptionalInt32::Set(const void* Data)
{
	Val = *((int32*)Data);
	IsSet = true;
}