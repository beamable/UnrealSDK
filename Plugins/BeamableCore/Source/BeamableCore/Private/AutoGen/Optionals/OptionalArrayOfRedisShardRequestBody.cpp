
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRedisShardRequestBody.h"

FOptionalArrayOfRedisShardRequestBody::FOptionalArrayOfRedisShardRequestBody()
{
	Val = TArray<URedisShardRequestBody*>();
	IsSet = false;
}

FOptionalArrayOfRedisShardRequestBody::FOptionalArrayOfRedisShardRequestBody(TArray<URedisShardRequestBody*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfRedisShardRequestBody::GetAddr() const { return &Val; }

void FOptionalArrayOfRedisShardRequestBody::Set(const void* Data)
{
	Val = *((TArray<URedisShardRequestBody*>*)Data);
	IsSet = true;
}