
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInt64.h"

FOptionalArrayOfInt64::FOptionalArrayOfInt64()
{
	Val = TArray<int64>();
	IsSet = false;
}

FOptionalArrayOfInt64::FOptionalArrayOfInt64(TArray<int64> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfInt64::GetAddr() const { return &Val; }

void FOptionalArrayOfInt64::Set(const void* Data)
{
	Val = *((TArray<int64>*)Data);
	IsSet = true;
}