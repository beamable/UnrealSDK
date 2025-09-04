#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateServicePlanRequestBody.h"

#include "CreateServicePlanRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateServicePlanRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Json", DisplayName="CreateServicePlanRequestBody To JSON String")
	static FString CreateServicePlanRequestBodyToJsonString(const UCreateServicePlanRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make CreateServicePlanRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bMongoSharded, bMongoTls, MongoHosts, MongoSrvAddress, RedisShards, MessageBusAnalytics, MessageBusCommon, Outer", NativeMakeFunc))
	static UCreateServicePlanRequestBody* Make(FString Name, FOptionalBool bMongoSharded, FOptionalBool bMongoTls, FOptionalString MongoHosts, FOptionalString MongoSrvAddress, FOptionalArrayOfRedisShardRequestBody RedisShards, FOptionalArrayOfString MessageBusAnalytics, FOptionalArrayOfString MessageBusCommon, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Break CreateServicePlanRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCreateServicePlanRequestBody* Serializable, FString& Name, FOptionalBool& bMongoSharded, FOptionalBool& bMongoTls, FOptionalString& MongoHosts, FOptionalString& MongoSrvAddress, FOptionalArrayOfRedisShardRequestBody& RedisShards, FOptionalArrayOfString& MessageBusAnalytics, FOptionalArrayOfString& MessageBusCommon);
};