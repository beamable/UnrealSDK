#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRedisShardRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"

#include "CreateServicePlanRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCreateServicePlanRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Mongo Sharded", Category="Beam")
	FOptionalBool bMongoSharded = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Mongo Tls", Category="Beam")
	FOptionalBool bMongoTls = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mongo Hosts", Category="Beam")
	FOptionalString MongoHosts = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mongo Srv Address", Category="Beam")
	FOptionalString MongoSrvAddress = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Redis Shards", Category="Beam")
	FOptionalArrayOfRedisShardRequestBody RedisShards = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Analytics", Category="Beam")
	FOptionalArrayOfString MessageBusAnalytics = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Common", Category="Beam")
	FOptionalArrayOfString MessageBusCommon = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};