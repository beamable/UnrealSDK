
#include "BeamableCore/Public/AutoGen/RedisShardRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void URedisShardRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("shardId"), ShardId);
	Serializer->WriteValue(TEXT("masterHost"), MasterHost);
	Serializer->WriteValue(TEXT("slaveHosts"), SlaveHosts);
}

void URedisShardRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("shardId"), ShardId);
	Serializer->WriteValue(TEXT("masterHost"), MasterHost);
	Serializer->WriteValue(TEXT("slaveHosts"), SlaveHosts);		
}

void URedisShardRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("shardId")), ShardId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("masterHost")), MasterHost);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("slaveHosts")), SlaveHosts);
}



