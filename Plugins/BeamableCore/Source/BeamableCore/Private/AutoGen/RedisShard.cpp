
#include "BeamableCore/Public/AutoGen/RedisShard.h"
#include "Serialization/BeamJsonUtils.h"




void URedisShard::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("shardId"), &ShardId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("masterHost"), &MasterHost, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("slaveHosts"), &SlaveHosts, Serializer);
}

void URedisShard::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("shardId"), &ShardId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("masterHost"), &MasterHost, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("slaveHosts"), &SlaveHosts, Serializer);		
}

void URedisShard::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("shardId", Bag, ShardId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("masterHost", Bag, MasterHost, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("slaveHosts", Bag, SlaveHosts, OuterOwner);
}



