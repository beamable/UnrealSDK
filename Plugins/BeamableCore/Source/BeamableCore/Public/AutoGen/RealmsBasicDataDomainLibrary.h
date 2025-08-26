#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicDataDomain.h"

#include "RealmsBasicDataDomainLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicDataDomainLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicDataDomain To JSON String")
	static FString RealmsBasicDataDomainToJsonString(const URealmsBasicDataDomain* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicDataDomain", meta=(DefaultToSelf="Outer", AdvancedDisplay="bMongoSSL, MongoSrvAddress, MessageBusAnalytics, MessageBusCommon, RedisShards, Outer", NativeMakeFunc))
	static URealmsBasicDataDomain* Make(bool bMongoSSLEnabled, bool bMongoSharded, TArray<FString> MemcachedHosts, TArray<FString> MongoHosts, FOptionalBool bMongoSSL, FOptionalString MongoSrvAddress, FOptionalArrayOfString MessageBusAnalytics, FOptionalArrayOfString MessageBusCommon, FOptionalArrayOfRedisShard RedisShards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicDataDomain", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicDataDomain* Serializable, bool& bMongoSSLEnabled, bool& bMongoSharded, TArray<FString>& MemcachedHosts, TArray<FString>& MongoHosts, FOptionalBool& bMongoSSL, FOptionalString& MongoSrvAddress, FOptionalArrayOfString& MessageBusAnalytics, FOptionalArrayOfString& MessageBusCommon, FOptionalArrayOfRedisShard& RedisShards);
};