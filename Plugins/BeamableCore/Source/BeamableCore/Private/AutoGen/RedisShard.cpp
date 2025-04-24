
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("shardId")), ShardId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("masterHost")), MasterHost);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("slaveHosts")), SlaveHosts, OuterOwner);
}



