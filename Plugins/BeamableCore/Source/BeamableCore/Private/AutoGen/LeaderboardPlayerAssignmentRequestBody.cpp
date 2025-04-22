
#include "BeamableCore/Public/AutoGen/LeaderboardPlayerAssignmentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void ULeaderboardPlayerAssignmentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("boardId"), BoardId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("joinBoard"), &bJoinBoard, Serializer);
}

void ULeaderboardPlayerAssignmentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("boardId"), BoardId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("joinBoard"), &bJoinBoard, Serializer);		
}

void ULeaderboardPlayerAssignmentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("boardId")), BoardId);
	UBeamJsonUtils::DeserializeOptional<bool>("joinBoard", Bag, bJoinBoard, OuterOwner);
}



