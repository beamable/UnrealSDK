
#pragma once

#include "CoreMinimal.h"
#include "RedisShardRequestBody.h"

#include "RedisShardRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URedisShardRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RedisShardRequestBody To JSON String")
	static FString RedisShardRequestBodyToJsonString(const URedisShardRequestBody* Serializable, const bool Pretty);		
};