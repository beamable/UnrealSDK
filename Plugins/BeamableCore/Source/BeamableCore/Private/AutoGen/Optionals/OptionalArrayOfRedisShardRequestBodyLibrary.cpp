

#include "AutoGen/Optionals/OptionalArrayOfRedisShardRequestBodyLibrary.h"

FOptionalArrayOfRedisShardRequestBody UOptionalArrayOfRedisShardRequestBodyLibrary::MakeOptional(TArray<URedisShardRequestBody*> Value)
{
	FOptionalArrayOfRedisShardRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRedisShardRequestBody UOptionalArrayOfRedisShardRequestBodyLibrary::Conv_OptionalFromValue(TArray<URedisShardRequestBody*> Value)
{
	FOptionalArrayOfRedisShardRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfRedisShardRequestBodyLibrary::HasValue(const FOptionalArrayOfRedisShardRequestBody& Optional, TArray<URedisShardRequestBody*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<URedisShardRequestBody*> UOptionalArrayOfRedisShardRequestBodyLibrary::GetOptionalValue(const FOptionalArrayOfRedisShardRequestBody& Optional, TArray<URedisShardRequestBody*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

