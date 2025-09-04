#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RedisShardRequestBody.h"

#include "RedisShardRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URedisShardRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Json", DisplayName="RedisShardRequestBody To JSON String")
	static FString RedisShardRequestBodyToJsonString(const URedisShardRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make RedisShardRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ShardId, MasterHost, SlaveHosts, Outer", NativeMakeFunc))
	static URedisShardRequestBody* Make(FOptionalInt32 ShardId, FOptionalString MasterHost, FOptionalString SlaveHosts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Break RedisShardRequestBody", meta=(NativeBreakFunc))
	static void Break(const URedisShardRequestBody* Serializable, FOptionalInt32& ShardId, FOptionalString& MasterHost, FOptionalString& SlaveHosts);
};