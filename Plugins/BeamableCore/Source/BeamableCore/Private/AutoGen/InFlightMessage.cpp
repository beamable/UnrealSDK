
#include "BeamableCore/Public/AutoGen/InFlightMessage.h"
#include "Serialization/BeamJsonUtils.h"




void UInFlightMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("method"), Method);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("path"), Path);
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("limitFailureRetries"), &bLimitFailureRetries, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
}

void UInFlightMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("method"), Method);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("path"), Path);
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("limitFailureRetries"), &bLimitFailureRetries, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);		
}

void UInFlightMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Method = Bag->GetStringField(TEXT("method"));
	Body = Bag->GetStringField(TEXT("body"));
	Path = Bag->GetStringField(TEXT("path"));
	Service = Bag->GetStringField(TEXT("service"));
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeOptional<bool>("limitFailureRetries", Bag, bLimitFailureRetries, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("shard", Bag, Shard, OuterOwner);
}



