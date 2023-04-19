
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInt32.h"

FOptionalArrayOfInt32::FOptionalArrayOfInt32()
{
	Val = TArray<int32>();
	IsSet = false;
}

FOptionalArrayOfInt32::FOptionalArrayOfInt32(TArray<int32> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfInt32::GetAddr() const { return &Val; }

void FOptionalArrayOfInt32::Set(const void* Data)
{
	Val = *((TArray<int32>*)Data);
	IsSet = true;
}