
#include "BeamableCore/Public/AutoGen/SteamAuthRequestBody.h"





void USteamAuthRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("ticket"), Ticket);
}

void USteamAuthRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("ticket"), Ticket);		
}

void USteamAuthRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Ticket = Bag->GetStringField(TEXT("ticket"));
}



