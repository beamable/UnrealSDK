
#include "BeamableCore/Public/AutoGen/LeaderboardAssignmentInfo.h"

#include "Misc/DefaultValueHelper.h"


void ULeaderboardAssignmentInfo::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULeaderboardAssignmentInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
}

void ULeaderboardAssignmentInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);		
}

void ULeaderboardAssignmentInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	LeaderboardId = Bag->GetStringField(TEXT("leaderboardId"));
}



