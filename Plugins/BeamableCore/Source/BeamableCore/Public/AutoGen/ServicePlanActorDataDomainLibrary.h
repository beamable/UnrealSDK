#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorDataDomain.h"

#include "ServicePlanActorDataDomainLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServicePlanActorDataDomainLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Json", DisplayName="ServicePlanActorDataDomain To JSON String")
	static FString ServicePlanActorDataDomainToJsonString(const UServicePlanActorDataDomain* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Make ServicePlanActorDataDomain", meta=(DefaultToSelf="Outer", AdvancedDisplay="bMongoSharded, bMongoTls, MongoSrvAddress, MongoHosts, MessageBusCommon, MessageBusAnalytics, RedisShards, Outer", NativeMakeFunc))
	static UServicePlanActorDataDomain* Make(FOptionalBool bMongoSharded, FOptionalBool bMongoTls, FOptionalString MongoSrvAddress, FOptionalArrayOfString MongoHosts, FOptionalArrayOfString MessageBusCommon, FOptionalArrayOfString MessageBusAnalytics, FOptionalArrayOfRedisShard RedisShards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Make/Break", DisplayName="Break ServicePlanActorDataDomain", meta=(NativeBreakFunc))
	static void Break(const UServicePlanActorDataDomain* Serializable, FOptionalBool& bMongoSharded, FOptionalBool& bMongoTls, FOptionalString& MongoSrvAddress, FOptionalArrayOfString& MongoHosts, FOptionalArrayOfString& MessageBusCommon, FOptionalArrayOfString& MessageBusAnalytics, FOptionalArrayOfRedisShard& RedisShards);
};