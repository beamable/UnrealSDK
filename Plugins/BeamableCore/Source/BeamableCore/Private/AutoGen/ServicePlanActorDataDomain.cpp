
#include "BeamableCore/Public/AutoGen/ServicePlanActorDataDomain.h"
#include "Serialization/BeamJsonUtils.h"




void UServicePlanActorDataDomain::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoSharded"), &bMongoSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoTls"), &bMongoTls, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("mongoHosts"), &MongoHosts, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URedisShard*>, URedisShard*>(TEXT("redisShards"), &RedisShards, Serializer);
}

void UServicePlanActorDataDomain::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoSharded"), &bMongoSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoTls"), &bMongoTls, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("mongoHosts"), &MongoHosts, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URedisShard*>, URedisShard*>(TEXT("redisShards"), &RedisShards, Serializer);		
}

void UServicePlanActorDataDomain::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("mongoSharded", Bag, bMongoSharded, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("mongoTls", Bag, bMongoTls, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("mongoSrvAddress", Bag, MongoSrvAddress, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("mongoHosts", Bag, MongoHosts, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusCommon", Bag, MessageBusCommon, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusAnalytics", Bag, MessageBusAnalytics, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URedisShard*>, URedisShard*>("redisShards", Bag, RedisShards, OuterOwner);
}



