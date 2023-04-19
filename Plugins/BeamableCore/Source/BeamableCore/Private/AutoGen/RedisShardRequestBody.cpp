
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
	ShardId = Bag->GetIntegerField(TEXT("shardId"));
	MasterHost = Bag->GetStringField(TEXT("masterHost"));
	SlaveHosts = Bag->GetStringField(TEXT("slaveHosts"));
}



