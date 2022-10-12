
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalArrayOfRedisShard.h"

#include "DataDomain.generated.h"

UCLASS(BlueprintType)
class UDataDomain : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Analytics")
	FOptionalArrayOfString MessageBusAnalytics;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Memcached Hosts")
	TArray<FString> MemcachedHosts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Mongo Sharded")
	bool bMongoSharded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Mongo SSL")
	FOptionalBool bMongoSSL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mongo Hosts")
	TArray<FString> MongoHosts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Mongo SSL Enabled")
	bool bMongoSSLEnabled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Common")
	FOptionalArrayOfString MessageBusCommon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Redis Shards")
	FOptionalArrayOfRedisShard RedisShards;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};