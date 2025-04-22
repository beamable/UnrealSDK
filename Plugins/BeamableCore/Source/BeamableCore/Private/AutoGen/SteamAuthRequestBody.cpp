
#include "BeamableCore/Public/AutoGen/SteamAuthRequestBody.h"





void USteamAuthRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("ticket"), Ticket, Serializer);
}

void USteamAuthRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("ticket"), Ticket, Serializer);		
}

void USteamAuthRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("ticket")), Ticket);
}



