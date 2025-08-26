
#include "BeamableCore/Public/AutoGen/RedisShardRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URedisShardRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("shardId"), &ShardId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("masterHost"), &MasterHost, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("slaveHosts"), &SlaveHosts, Serializer);
}

void URedisShardRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("shardId"), &ShardId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("masterHost"), &MasterHost, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("slaveHosts"), &SlaveHosts, Serializer);		
}

void URedisShardRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("shardId", Bag, ShardId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("masterHost", Bag, MasterHost, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("slaveHosts", Bag, SlaveHosts, OuterOwner);
}



