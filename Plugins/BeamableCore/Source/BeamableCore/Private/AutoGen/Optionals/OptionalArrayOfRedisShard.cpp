
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRedisShard.h"

FOptionalArrayOfRedisShard::FOptionalArrayOfRedisShard()
{
	Val = TArray<URedisShard*>();
	IsSet = false;
}

FOptionalArrayOfRedisShard::FOptionalArrayOfRedisShard(TArray<URedisShard*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfRedisShard::GetAddr() const { return &Val; }

void FOptionalArrayOfRedisShard::Set(const void* Data)
{
	Val = *((TArray<URedisShard*>*)Data);
	IsSet = true;
}