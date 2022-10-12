
#include "AutoGen/PlayerIdRequestBody.h"



void UPlayerIdRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
}

void UPlayerIdRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);		
}

void UPlayerIdRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PlayerId = Bag->GetStringField(TEXT("playerId"));
}