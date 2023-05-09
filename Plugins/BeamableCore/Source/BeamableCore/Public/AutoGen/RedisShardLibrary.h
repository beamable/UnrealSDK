#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RedisShard.h"

#include "RedisShardLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URedisShardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RedisShard To JSON String")
	static FString RedisShardToJsonString(const URedisShard* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RedisShard", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URedisShard* Make(int32 ShardId, FString MasterHost, TArray<FString> SlaveHosts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RedisShard", meta=(NativeBreakFunc))
	static void Break(const URedisShard* Serializable, int32& ShardId, FString& MasterHost, TArray<FString>& SlaveHosts);
};