
#include "BeamableCore/Public/AutoGen/EventPlayerGroupState.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPlayerGroupState::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groupScore"), GroupScore, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groupRank"), GroupRank, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("rankRewards"), RankRewards, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("scoreRewards"), ScoreRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);
}

void UEventPlayerGroupState::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groupScore"), GroupScore, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groupRank"), GroupRank, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("rankRewards"), RankRewards, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("scoreRewards"), ScoreRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);		
}

void UEventPlayerGroupState::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("groupScore"), Bag, GroupScore);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("groupRank"), Bag, GroupRank);
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(TEXT("rankRewards"), Bag, RankRewards, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(TEXT("scoreRewards"), Bag, ScoreRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("groupId", Bag, GroupId, OuterOwner);
}



