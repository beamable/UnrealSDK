

#include "AutoGen/Optionals/OptionalArrayOfRedisShardLibrary.h"

FOptionalArrayOfRedisShard UOptionalArrayOfRedisShardLibrary::MakeOptional(TArray<URedisShard*> Value)
{
	FOptionalArrayOfRedisShard Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRedisShard UOptionalArrayOfRedisShardLibrary::Conv_OptionalFromValue(TArray<URedisShard*> Value)
{
	FOptionalArrayOfRedisShard Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfRedisShardLibrary::HasValue(const FOptionalArrayOfRedisShard& Optional, TArray<URedisShard*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<URedisShard*> UOptionalArrayOfRedisShardLibrary::GetOptionalValue(const FOptionalArrayOfRedisShard& Optional, TArray<URedisShard*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

