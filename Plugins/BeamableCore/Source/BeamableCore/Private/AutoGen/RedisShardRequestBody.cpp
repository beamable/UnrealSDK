
#include "BeamableCore/Public/AutoGen/RedisShardRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void URedisShardRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("shardId"), ShardId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("masterHost"), MasterHost, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slaveHosts"), SlaveHosts, Serializer);
}

void URedisShardRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("shardId"), ShardId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("masterHost"), MasterHost, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slaveHosts"), SlaveHosts, Serializer);		
}

void URedisShardRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("shardId")), ShardId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("masterHost")), MasterHost);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("slaveHosts")), SlaveHosts);
}



