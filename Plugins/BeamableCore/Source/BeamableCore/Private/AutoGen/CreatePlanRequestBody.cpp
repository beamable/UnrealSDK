
#include "BeamableCore/Public/AutoGen/CreatePlanRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCreatePlanRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mongoSSL"), bMongoSSL, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sharded"), bSharded, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("memcachedHosts"), MemcachedHosts, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platformJBDC"), PlatformJBDC, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mongoHosts"), MongoHosts, Serializer);
	UBeamJsonUtils::SerializeArray<URedisShardRequestBody*>(TEXT("redisShards"), RedisShards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
}

void UCreatePlanRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mongoSSL"), bMongoSSL, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sharded"), bSharded, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("memcachedHosts"), MemcachedHosts, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platformJBDC"), PlatformJBDC, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mongoHosts"), MongoHosts, Serializer);
	UBeamJsonUtils::SerializeArray<URedisShardRequestBody*>(TEXT("redisShards"), RedisShards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);		
}

void UCreatePlanRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("mongoSSL"), Bag, bMongoSSL);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("sharded"), Bag, bSharded);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("memcachedHosts"), Bag, MemcachedHosts);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("platformJBDC"), Bag, PlatformJBDC);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("mongoHosts"), Bag, MongoHosts);
	UBeamJsonUtils::DeserializeArray<URedisShardRequestBody*>(TEXT("redisShards"), Bag, RedisShards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("mongoSrvAddress", Bag, MongoSrvAddress, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusAnalytics", Bag, MessageBusAnalytics, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusCommon", Bag, MessageBusCommon, OuterOwner);
}



