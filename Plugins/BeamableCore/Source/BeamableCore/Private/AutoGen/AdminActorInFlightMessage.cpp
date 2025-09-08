
#include "BeamableCore/Public/AutoGen/AdminActorInFlightMessage.h"
#include "Serialization/BeamJsonUtils.h"




void UAdminActorInFlightMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("messageId"), MessageId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("method"), Method, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("path"), Path, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("limitFailureRetries"), &bLimitFailureRetries, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
}

void UAdminActorInFlightMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("messageId"), MessageId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("method"), Method, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("path"), Path, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("limitFailureRetries"), &bLimitFailureRetries, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);		
}

void UAdminActorInFlightMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("service"), Bag, Service);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("messageId"), Bag, MessageId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("method"), Bag, Method);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("path"), Bag, Path);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("body"), Bag, Body);
	UBeamJsonUtils::DeserializeOptional<bool>("limitFailureRetries", Bag, bLimitFailureRetries, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("shard", Bag, Shard, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
}



