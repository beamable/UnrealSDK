
#include "AutoGen/DataDomain.h"
#include "Serialization/BeamJsonUtils.h"


void UDataDomain ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("memcachedHosts"), MemcachedHosts, Serializer);
	Serializer->WriteValue(TEXT("mongoSharded"), bMongoSharded);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoSSL"), &bMongoSSL, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("mongoHosts"), MongoHosts, Serializer);
	Serializer->WriteValue(TEXT("mongoSSLEnabled"), bMongoSSLEnabled);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URedisShard*>, URedisShard*>(TEXT("redisShards"), &RedisShards, Serializer);
}

void UDataDomain::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("memcachedHosts"), MemcachedHosts, Serializer);
	Serializer->WriteValue(TEXT("mongoSharded"), bMongoSharded);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("mongoSSL"), &bMongoSSL, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("mongoHosts"), MongoHosts, Serializer);
	Serializer->WriteValue(TEXT("mongoSSLEnabled"), bMongoSSLEnabled);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URedisShard*>, URedisShard*>(TEXT("redisShards"), &RedisShards, Serializer);		
}

void UDataDomain ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusAnalytics", Bag, MessageBusAnalytics, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("memcachedHosts")), MemcachedHosts, OuterOwner);
	bMongoSharded = Bag->GetBoolField(TEXT("mongoSharded"));
	UBeamJsonUtils::DeserializeOptional<bool>("mongoSSL", Bag, bMongoSSL, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("mongoHosts")), MongoHosts, OuterOwner);
	bMongoSSLEnabled = Bag->GetBoolField(TEXT("mongoSSLEnabled"));
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusCommon", Bag, MessageBusCommon, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URedisShard*>, URedisShard*>("redisShards", Bag, RedisShards, OuterOwner);
}