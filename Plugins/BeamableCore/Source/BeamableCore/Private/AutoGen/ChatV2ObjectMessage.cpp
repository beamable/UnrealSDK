
#include "AutoGen/ChatV2ObjectMessage.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UChatV2ObjectMessage ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("roomId"), RoomId);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	Serializer->WriteValue(TEXT("timestampMillis"), TimestampMillis);
	Serializer->WriteValue(TEXT("censoredContent"), CensoredContent);
	Serializer->WriteValue(TEXT("messageId"), MessageId.ToString());
	Serializer->WriteValue(TEXT("content"), Content);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("reactions"), Reactions, Serializer);
}

void UChatV2ObjectMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("roomId"), RoomId);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	Serializer->WriteValue(TEXT("timestampMillis"), TimestampMillis);
	Serializer->WriteValue(TEXT("censoredContent"), CensoredContent);
	Serializer->WriteValue(TEXT("messageId"), MessageId.ToString());
	Serializer->WriteValue(TEXT("content"), Content);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("reactions"), Reactions, Serializer);		
}

void UChatV2ObjectMessage ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	RoomId = Bag->GetStringField(TEXT("roomId"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("timestampMillis")), TimestampMillis);
	CensoredContent = Bag->GetStringField(TEXT("censoredContent"));
	FGuid::Parse(Bag->GetStringField(TEXT("messageId")), MessageId);
	Content = Bag->GetStringField(TEXT("content"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("reactions")), Reactions, OuterOwner);
}