
#include "BeamableCore/Public/AutoGen/RedisShard.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void URedisShard::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("shardId"), ShardId);
	Serializer->WriteValue(TEXT("masterHost"), MasterHost);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("slaveHosts"), SlaveHosts, Serializer);
}

void URedisShard::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("shardId"), ShardId);
	Serializer->WriteValue(TEXT("masterHost"), MasterHost);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("slaveHosts"), SlaveHosts, Serializer);		
}

void URedisShard::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("shardId")), ShardId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("masterHost")), MasterHost);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("slaveHosts")), SlaveHosts, OuterOwner);
}



