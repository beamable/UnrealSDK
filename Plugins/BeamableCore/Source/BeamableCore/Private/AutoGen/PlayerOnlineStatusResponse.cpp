
#include "BeamableCore/Public/AutoGen/PlayerOnlineStatusResponse.h"

#include "Misc/DefaultValueHelper.h"



void UPlayerOnlineStatusResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("online"), bOnline);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("lastSeen"), LastSeen);
}

void UPlayerOnlineStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("online"), bOnline);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("lastSeen"), LastSeen);		
}

void UPlayerOnlineStatusResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bOnline = Bag->GetBoolField(TEXT("online"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("lastSeen")), LastSeen);
}



