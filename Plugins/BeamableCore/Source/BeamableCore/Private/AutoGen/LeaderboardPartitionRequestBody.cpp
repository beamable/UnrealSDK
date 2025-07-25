
#include "BeamableCore/Public/AutoGen/LeaderboardPartitionRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardPartitionRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
}

void ULeaderboardPartitionRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);		
}

void ULeaderboardPartitionRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
}



