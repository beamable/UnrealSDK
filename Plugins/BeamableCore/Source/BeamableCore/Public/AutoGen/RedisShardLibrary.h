#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RedisShard.h"

#include "RedisShardLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URedisShardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Json", DisplayName="RedisShard To JSON String")
	static FString RedisShardToJsonString(const URedisShard* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make RedisShard", meta=(DefaultToSelf="Outer", AdvancedDisplay="ShardId, MasterHost, SlaveHosts, Outer", NativeMakeFunc))
	static URedisShard* Make(FOptionalInt32 ShardId, FOptionalString MasterHost, FOptionalArrayOfString SlaveHosts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Break RedisShard", meta=(NativeBreakFunc))
	static void Break(const URedisShard* Serializable, FOptionalInt32& ShardId, FOptionalString& MasterHost, FOptionalArrayOfString& SlaveHosts);
};