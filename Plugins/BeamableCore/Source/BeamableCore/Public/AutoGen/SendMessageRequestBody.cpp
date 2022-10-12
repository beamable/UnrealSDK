
#include "AutoGen/SendMessageRequestBody.h"



void USendMessageRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("roomId"), RoomId);
	Serializer->WriteValue(TEXT("content"), Content);
}

void USendMessageRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("roomId"), RoomId);
	Serializer->WriteValue(TEXT("content"), Content);		
}

void USendMessageRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	RoomId = Bag->GetStringField(TEXT("roomId"));
	Content = Bag->GetStringField(TEXT("content"));
}