#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RedisShardRequestBody.h"

#include "RedisShardRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URedisShardRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RedisShardRequestBody To JSON String")
	static FString RedisShardRequestBodyToJsonString(const URedisShardRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RedisShardRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URedisShardRequestBody* Make(int32 ShardId, FString MasterHost, FString SlaveHosts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RedisShardRequestBody", meta=(NativeBreakFunc))
	static void Break(const URedisShardRequestBody* Serializable, int32& ShardId, FString& MasterHost, FString& SlaveHosts);
};