
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
	bMongoSSL = Bag->GetBoolField(TEXT("mongoSSL"));
	bSharded = Bag->GetBoolField(TEXT("sharded"));
	Name = Bag->GetStringField(TEXT("name"));
	MemcachedHosts = Bag->GetStringField(TEXT("memcachedHosts"));
	PlatformJBDC = Bag->GetStringField(TEXT("platformJBDC"));
	MongoHosts = Bag->GetStringField(TEXT("mongoHosts"));
	UBeamJsonUtils::DeserializeArray<URedisShardRequestBody*>(Bag->GetArrayField(TEXT("redisShards")), RedisShards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("mongoSrvAddress", Bag, MongoSrvAddress, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusAnalytics", Bag, MessageBusAnalytics, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("messageBusCommon", Bag, MessageBusCommon, OuterOwner);
}



