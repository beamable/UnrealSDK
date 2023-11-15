#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreatePlanRequestBody.h"

#include "CreatePlanRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreatePlanRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CreatePlanRequestBody To JSON String")
	static FString CreatePlanRequestBodyToJsonString(const UCreatePlanRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CreatePlanRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="MongoSrvAddress, MessageBusAnalytics, MessageBusCommon, Outer", NativeMakeFunc))
	static UCreatePlanRequestBody* Make(bool bMongoSSL, bool bSharded, FString Name, FString MemcachedHosts, FString PlatformJBDC, FString MongoHosts, TArray<URedisShardRequestBody*> RedisShards, FOptionalString MongoSrvAddress, FOptionalArrayOfString MessageBusAnalytics, FOptionalArrayOfString MessageBusCommon, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CreatePlanRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCreatePlanRequestBody* Serializable, bool& bMongoSSL, bool& bSharded, FString& Name, FString& MemcachedHosts, FString& PlatformJBDC, FString& MongoHosts, TArray<URedisShardRequestBody*>& RedisShards, FOptionalString& MongoSrvAddress, FOptionalArrayOfString& MessageBusAnalytics, FOptionalArrayOfString& MessageBusCommon);
};