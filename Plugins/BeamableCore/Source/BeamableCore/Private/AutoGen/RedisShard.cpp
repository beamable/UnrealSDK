
#include "BeamableCore/Public/AutoGen/RedisShard.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void URedisShard::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("shardId"), ShardId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("masterHost"), MasterHost, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("slaveHosts"), SlaveHosts, Serializer);
}

void URedisShard::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("shardId"), ShardId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("masterHost"), MasterHost, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("slaveHosts"), SlaveHosts, Serializer);		
}

void URedisShard::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("shardId"), Bag, ShardId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("masterHost"), Bag, MasterHost);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("slaveHosts"), Bag, SlaveHosts, OuterOwner);
}



