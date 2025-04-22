
#include "BeamableCore/Public/AutoGen/InFlightMessage.h"
#include "Serialization/BeamJsonUtils.h"




void UInFlightMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("method"), Method, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("path"), Path, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("limitFailureRetries"), &bLimitFailureRetries, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
}

void UInFlightMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("method"), Method, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("path"), Path, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("limitFailureRetries"), &bLimitFailureRetries, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);		
}

void UInFlightMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("method")), Method);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("body")), Body);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("path")), Path);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("service")), Service);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeOptional<bool>("limitFailureRetries", Bag, bLimitFailureRetries, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("shard", Bag, Shard, OuterOwner);
}



