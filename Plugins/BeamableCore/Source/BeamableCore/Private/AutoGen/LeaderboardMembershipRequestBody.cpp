
#include "BeamableCore/Public/AutoGen/LeaderboardMembershipRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardMembershipRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
}

void ULeaderboardMembershipRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);		
}

void ULeaderboardMembershipRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
}



