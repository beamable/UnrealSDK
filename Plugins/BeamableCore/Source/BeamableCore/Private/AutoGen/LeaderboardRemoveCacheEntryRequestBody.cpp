
#include "BeamableCore/Public/AutoGen/LeaderboardRemoveCacheEntryRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardRemoveCacheEntryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
}

void ULeaderboardRemoveCacheEntryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);		
}

void ULeaderboardRemoveCacheEntryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
}



