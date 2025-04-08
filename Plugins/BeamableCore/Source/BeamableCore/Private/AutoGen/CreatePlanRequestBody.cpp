
#include "BeamableCore/Public/AutoGen/CreatePlanRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCreatePlanRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("mongoSSL"), bMongoSSL);
	Serializer->WriteValue(TEXT("sharded"), bSharded);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("memcachedHosts"), MemcachedHosts);
	Serializer->WriteValue(TEXT("platformJBDC"), PlatformJBDC);
	Serializer->WriteValue(TEXT("mongoHosts"), MongoHosts);
	UBeamJsonUtils::SerializeArray<URedisShardRequestBody*>(TEXT("redisShards"), RedisShards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
}

void UCreatePlanRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("mongoSSL"), bMongoSSL);
	Serializer->WriteValue(TEXT("sharded"), bSharded);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("memcachedHosts"), MemcachedHosts);
	Serializer->WriteValue(TEXT("platformJBDC"), PlatformJBDC);
	Serializer->WriteValue(TEXT("mongoHosts"), MongoHosts);
	UBeamJsonUtils::SerializeArray<URedisShardRequestBody*>(TEXT("redisShards"), RedisShards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("mongoSrvAddress"), &MongoSrvAddress, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);		
}

void UCreatePlanRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("mongoSSL")), bMongoSSL);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sharded")), bSharded);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("memcachedHosts")), MemcachedHosts);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("platformJBDC")), PlatformJBDC);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("mongoHosts")), MongoHosts);
	UBeamJsonUtils::DeserializeArray<URedisShardRequestBody*>(Bag->GetArrayField(TEXT("redisShards")), RedisShards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("mongoSrvAddress", Bag, MongoSrvAddress, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusAnalytics", Bag, MessageBusAnalytics, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusCommon", Bag, MessageBusCommon, OuterOwner);
}



