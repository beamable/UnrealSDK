#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/RedisShardRequestBody.h"

#include "CreatePlanRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCreatePlanRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Mongo SSL", Category="Beam")
	bool bMongoSSL = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded", Category="Beam")
	bool bSharded = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Memcached Hosts", Category="Beam")
	FString MemcachedHosts = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Platform JBDC", Category="Beam")
	FString PlatformJBDC = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mongo Hosts", Category="Beam")
	FString MongoHosts = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Redis Shards", Category="Beam")
	TArray<URedisShardRequestBody*> RedisShards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mongo Srv Address", Category="Beam")
	FOptionalString MongoSrvAddress = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Analytics", Category="Beam")
	FOptionalArrayOfString MessageBusAnalytics = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Common", Category="Beam")
	FOptionalArrayOfString MessageBusCommon = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};