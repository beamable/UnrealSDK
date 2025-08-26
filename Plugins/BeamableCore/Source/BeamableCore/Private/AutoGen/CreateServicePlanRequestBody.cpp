
#include "BeamableCore/Public/AutoGen/CreateServicePlanRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCreateServicePlanRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoSharded"), &bMongoSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoTls"), &bMongoTls, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoHosts"), &MongoHosts, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URedisShardRequestBody*>, URedisShardRequestBody*>(TEXT("redisShards"), &RedisShards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
}

void UCreateServicePlanRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoSharded"), &bMongoSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoTls"), &bMongoTls, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoHosts"), &MongoHosts, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URedisShardRequestBody*>, URedisShardRequestBody*>(TEXT("redisShards"), &RedisShards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);		
}

void UCreateServicePlanRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeOptional<bool>("mongoSharded", Bag, bMongoSharded, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("mongoTls", Bag, bMongoTls, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("mongoHosts", Bag, MongoHosts, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("mongoSrvAddress", Bag, MongoSrvAddress, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URedisShardRequestBody*>, URedisShardRequestBody*>("redisShards", Bag, RedisShards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusAnalytics", Bag, MessageBusAnalytics, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusCommon", Bag, MessageBusCommon, OuterOwner);
}



