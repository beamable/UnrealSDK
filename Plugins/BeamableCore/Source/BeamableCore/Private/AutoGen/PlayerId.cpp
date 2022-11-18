
#include "AutoGen/PlayerId.h"





void UPlayerId ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
}

void UPlayerId::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);		
}

void UPlayerId ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PlayerId = Bag->GetStringField(TEXT("playerId"));
}