
#include "BeamableCore/Public/AutoGen/LeaderboardRemoveCacheEntryRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardRemoveCacheEntryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
}

void ULeaderboardRemoveCacheEntryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);		
}

void ULeaderboardRemoveCacheEntryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
}



