
#include "AutoGen/CreatePlanRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void UCreatePlanRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	Serializer->WriteValue(TEXT("memcachedHosts"), MemcachedHosts);
	Serializer->WriteValue(TEXT("mongoSSL"), bMongoSSL);
	Serializer->WriteValue(TEXT("platformJBDC"), PlatformJBDC);
	Serializer->WriteValue(TEXT("sharded"), bSharded);
	Serializer->WriteValue(TEXT("mongoHosts"), MongoHosts);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
	UBeamJsonUtils::SerializeArray<URedisShardRequestBody*>(TEXT("redisShards"), RedisShards, Serializer);
}

void UCreatePlanRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusAnalytics"), &MessageBusAnalytics, Serializer);
	Serializer->WriteValue(TEXT("memcachedHosts"), MemcachedHosts);
	Serializer->WriteValue(TEXT("mongoSSL"), bMongoSSL);
	Serializer->WriteValue(TEXT("platformJBDC"), PlatformJBDC);
	Serializer->WriteValue(TEXT("sharded"), bSharded);
	Serializer->WriteValue(TEXT("mongoHosts"), MongoHosts);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("messageBusCommon"), &MessageBusCommon, Serializer);
	UBeamJsonUtils::SerializeArray<URedisShardRequestBody*>(TEXT("redisShards"), RedisShards, Serializer);		
}

void UCreatePlanRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusAnalytics", Bag, MessageBusAnalytics, OuterOwner);
	MemcachedHosts = Bag->GetStringField(TEXT("memcachedHosts"));
	bMongoSSL = Bag->GetBoolField(TEXT("mongoSSL"));
	PlatformJBDC = Bag->GetStringField(TEXT("platformJBDC"));
	bSharded = Bag->GetBoolField(TEXT("sharded"));
	MongoHosts = Bag->GetStringField(TEXT("mongoHosts"));
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusCommon", Bag, MessageBusCommon, OuterOwner);
	UBeamJsonUtils::DeserializeArray<URedisShardRequestBody*>(Bag->GetArrayField(TEXT("redisShards")), RedisShards, OuterOwner);
}