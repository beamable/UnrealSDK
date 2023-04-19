
#include "BeamableCore/Public/AutoGen/LeaderboardPlayerAssignmentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void ULeaderboardPlayerAssignmentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("boardId"), BoardId);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("joinBoard"), &bJoinBoard, Serializer);
}

void ULeaderboardPlayerAssignmentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("boardId"), BoardId);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("joinBoard"), &bJoinBoard, Serializer);		
}

void ULeaderboardPlayerAssignmentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	BoardId = Bag->GetStringField(TEXT("boardId"));
	UBeamJsonUtils::DeserializeOptional<bool>("joinBoard", Bag, bJoinBoard, OuterOwner);
}



