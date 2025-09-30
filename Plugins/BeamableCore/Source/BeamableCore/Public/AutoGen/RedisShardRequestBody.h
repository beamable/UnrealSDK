#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "RedisShardRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API URedisShardRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Shard Id", Category="Beam")
	FOptionalInt32 ShardId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Master Host", Category="Beam")
	FOptionalString MasterHost = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Slave Hosts", Category="Beam")
	FOptionalString SlaveHosts = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};