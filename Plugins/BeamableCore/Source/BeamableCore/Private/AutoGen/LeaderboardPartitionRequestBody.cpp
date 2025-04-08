
#include "BeamableCore/Public/AutoGen/LeaderboardPartitionRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardPartitionRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
}

void ULeaderboardPartitionRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);		
}

void ULeaderboardPartitionRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
}



