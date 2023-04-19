
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
	ShardId = Bag->GetIntegerField(TEXT("shardId"));
	MasterHost = Bag->GetStringField(TEXT("masterHost"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("slaveHosts")), SlaveHosts, OuterOwner);
}



