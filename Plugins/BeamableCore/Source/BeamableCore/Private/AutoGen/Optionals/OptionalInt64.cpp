
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

FOptionalInt64::FOptionalInt64()
{
	Val = int64();
	IsSet = false;
}

FOptionalInt64::FOptionalInt64(int64 Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalInt64::GetAddr() const { return &Val; }

void FOptionalInt64::Set(const void* Data)
{
	Val = *((int64*)Data);
	IsSet = true;
}