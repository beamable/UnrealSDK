
#include "BeamableCore/Public/AutoGen/DataDomain.h"
#include "Serialization/BeamJsonUtils.h"




void UDataDomain::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mongoSSLEnabled"), bMongoSSLEnabled, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mongoSharded"), bMongoSharded, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("memcachedHosts"), MemcachedHosts, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("mongoHosts"), MongoHosts, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoSSL"), &bMongoSSL, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URedisShard*>, URedisShard*>(TEXT("redisShards"), &RedisShards, Serializer);
}

void UDataDomain::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mongoSSLEnabled"), bMongoSSLEnabled, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("mongoSharded"), bMongoSharded, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("memcachedHosts"), MemcachedHosts, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("mongoHosts"), MongoHosts, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoSSL"), &bMongoSSL, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URedisShard*>, URedisShard*>(TEXT("redisShards"), &RedisShards, Serializer);		
}

void UDataDomain::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("mongoSSLEnabled"), Bag, bMongoSSLEnabled);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("mongoSharded"), Bag, bMongoSharded);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("memcachedHosts"), Bag, MemcachedHosts, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("mongoHosts"), Bag, MongoHosts, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("mongoSSL", Bag, bMongoSSL, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("mongoSrvAddress", Bag, MongoSrvAddress, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusAnalytics", Bag, MessageBusAnalytics, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusCommon", Bag, MessageBusCommon, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URedisShard*>, URedisShard*>("redisShards", Bag, RedisShards, OuterOwner);
}



