
#include "BeamableCore/Public/AutoGen/PlayerOnlineStatusResponse.h"

#include "Misc/DefaultValueHelper.h"



void UPlayerOnlineStatusResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("online"), bOnline, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastSeen"), LastSeen, Serializer);
}

void UPlayerOnlineStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("online"), bOnline, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastSeen"), LastSeen, Serializer);		
}

void UPlayerOnlineStatusResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("online"), Bag, bOnline);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lastSeen"), Bag, LastSeen);
}



