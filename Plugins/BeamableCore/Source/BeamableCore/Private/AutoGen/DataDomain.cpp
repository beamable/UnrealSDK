
#include "BeamableCore/Public/AutoGen/DataDomain.h"
#include "Serialization/BeamJsonUtils.h"




void UDataDomain::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("mongoSSLEnabled"), bMongoSSLEnabled);
	Serializer->WriteValue(TEXT("mongoSharded"), bMongoSharded);
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
	Serializer->WriteValue(TEXT("mongoSSLEnabled"), bMongoSSLEnabled);
	Serializer->WriteValue(TEXT("mongoSharded"), bMongoSharded);
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("mongoSSLEnabled")), bMongoSSLEnabled);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("mongoSharded")), bMongoSharded);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("memcachedHosts")), MemcachedHosts, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("mongoHosts")), MongoHosts, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("mongoSSL", Bag, bMongoSSL, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("mongoSrvAddress", Bag, MongoSrvAddress, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusAnalytics", Bag, MessageBusAnalytics, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusCommon", Bag, MessageBusCommon, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URedisShard*>, URedisShard*>("redisShards", Bag, RedisShards, OuterOwner);
}



