
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfInt64.h"

FOptionalMapOfInt64::FOptionalMapOfInt64()
{
	Val = TMap<FString, int64>();
	IsSet = false;
}

FOptionalMapOfInt64::FOptionalMapOfInt64(TMap<FString, int64> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMapOfInt64::GetAddr() const { return &Val; }

void FOptionalMapOfInt64::Set(const void* Data)
{
	Val = *((TMap<FString, int64>*)Data);
	IsSet = true;
}