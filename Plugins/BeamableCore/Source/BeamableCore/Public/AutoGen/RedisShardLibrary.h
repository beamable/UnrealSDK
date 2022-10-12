
#pragma once

#include "CoreMinimal.h"
#include "RedisShard.h"

#include "RedisShardLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URedisShardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RedisShard To JSON String")
	static FString RedisShardToJsonString(const URedisShard* Serializable, const bool Pretty);		
};