
#include "AutoGen/InFlightMessage.h"
#include "Serialization/BeamJsonUtils.h"


void UInFlightMessage ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("method"), Method);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("path"), Path);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("id"), Id);
}

void UInFlightMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("method"), Method);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("path"), Path);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("id"), Id);		
}

void UInFlightMessage ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Method = Bag->GetStringField(TEXT("method"));
	Body = Bag->GetStringField(TEXT("body"));
	Path = Bag->GetStringField(TEXT("path"));
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("shard", Bag, Shard, OuterOwner);
	Service = Bag->GetStringField(TEXT("service"));
	Id = Bag->GetStringField(TEXT("id"));
}