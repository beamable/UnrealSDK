

#include "OptionalArrayOfRedisShardLibrary.h"

FOptionalArrayOfRedisShard UOptionalArrayOfRedisShardLibrary::MakeOptionalArrayOfRedisShard(TArray<URedisShard*> Value)
{
	FOptionalArrayOfRedisShard Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRedisShard UOptionalArrayOfRedisShardLibrary::Conv_OptionalArrayOfRedisShardFromValue(TArray<URedisShard*> Value)
{
	FOptionalArrayOfRedisShard Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

