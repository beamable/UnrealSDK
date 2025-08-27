
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("shardId"), Bag, ShardId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("masterHost"), Bag, MasterHost);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("slaveHosts"), Bag, SlaveHosts);
}



