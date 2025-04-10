#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DataDomain.h"

#include "DataDomainLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDataDomainLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|4 - Json", DisplayName="DataDomain To JSON String")
	static FString DataDomainToJsonString(const UDataDomain* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|3 - Backend", DisplayName="Make DataDomain", meta=(DefaultToSelf="Outer", AdvancedDisplay="bMongoSSL, MongoSrvAddress, MessageBusAnalytics, MessageBusCommon, RedisShards, Outer", NativeMakeFunc))
	static UDataDomain* Make(bool bMongoSSLEnabled, bool bMongoSharded, TArray<FString> MemcachedHosts, TArray<FString> MongoHosts, FOptionalBool bMongoSSL, FOptionalString MongoSrvAddress, FOptionalArrayOfString MessageBusAnalytics, FOptionalArrayOfString MessageBusCommon, FOptionalArrayOfRedisShard RedisShards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|3 - Backend", DisplayName="Break DataDomain", meta=(NativeBreakFunc))
	static void Break(const UDataDomain* Serializable, bool& bMongoSSLEnabled, bool& bMongoSharded, TArray<FString>& MemcachedHosts, TArray<FString>& MongoHosts, FOptionalBool& bMongoSSL, FOptionalString& MongoSrvAddress, FOptionalArrayOfString& MessageBusAnalytics, FOptionalArrayOfString& MessageBusCommon, FOptionalArrayOfRedisShard& RedisShards);
};