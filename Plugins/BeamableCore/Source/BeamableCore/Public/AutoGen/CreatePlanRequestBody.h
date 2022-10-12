
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfString.h"
#include "AutoGen/RedisShardRequestBody.h"

#include "CreatePlanRequestBody.generated.h"

UCLASS(BlueprintType)
class UCreatePlanRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Analytics")
	FOptionalArrayOfString MessageBusAnalytics;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Memcached Hosts")
	FString MemcachedHosts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Mongo SSL")
	bool bMongoSSL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Platform JBDC")
	FString PlatformJBDC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded")
	bool bSharded;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mongo Hosts")
	FString MongoHosts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Common")
	FOptionalArrayOfString MessageBusCommon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Redis Shards")
	TArray<URedisShardRequestBody*> RedisShards;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};