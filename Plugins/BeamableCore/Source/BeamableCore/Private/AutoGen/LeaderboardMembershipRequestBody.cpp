
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
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
}



