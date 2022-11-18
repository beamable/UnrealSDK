
#include "AutoGen/RoomInfo.h"
#include "Serialization/BeamJsonUtils.h"




void URoomInfo ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("keepSubscribed"), bKeepSubscribed);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<TArray<int64>, int64>(TEXT("players"), &Players, Serializer);
}

void URoomInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("keepSubscribed"), bKeepSubscribed);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<TArray<int64>, int64>(TEXT("players"), &Players, Serializer);		
}

void URoomInfo ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bKeepSubscribed = Bag->GetBoolField(TEXT("keepSubscribed"));
	Id = Bag->GetStringField(TEXT("id"));
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeOptional<TArray<int64>, int64>("players", Bag, Players, OuterOwner);
}