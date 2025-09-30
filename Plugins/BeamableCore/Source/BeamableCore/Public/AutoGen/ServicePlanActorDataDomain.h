#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRedisShard.h"

#include "ServicePlanActorDataDomain.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UServicePlanActorDataDomain : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Mongo Sharded", Category="Beam")
	FOptionalBool bMongoSharded = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Mongo Tls", Category="Beam")
	FOptionalBool bMongoTls = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mongo Srv Address", Category="Beam")
	FOptionalString MongoSrvAddress = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Mongo Hosts", Category="Beam")
	FOptionalArrayOfString MongoHosts = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Common", Category="Beam")
	FOptionalArrayOfString MessageBusCommon = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Bus Analytics", Category="Beam")
	FOptionalArrayOfString MessageBusAnalytics = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Redis Shards", Category="Beam")
	FOptionalArrayOfRedisShard RedisShards = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};