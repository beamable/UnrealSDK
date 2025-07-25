
#include "BeamableCore/Public/AutoGen/EventPlayerStateView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPlayerStateView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("running"), bRunning, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("secondsRemaining"), SecondsRemaining, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leaderboardId"), LeaderboardId, Serializer);
	UBeamJsonUtils::SerializeArray<UEventPlayerPhaseView*>(TEXT("allPhases"), AllPhases, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("rankRewards"), RankRewards, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("scoreRewards"), ScoreRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPlayerPhaseView*>(TEXT("currentPhase"), &CurrentPhase, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPlayerGroupState*>(TEXT("groupRewards"), &GroupRewards, Serializer);
}

void UEventPlayerStateView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("running"), bRunning, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("secondsRemaining"), SecondsRemaining, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leaderboardId"), LeaderboardId, Serializer);
	UBeamJsonUtils::SerializeArray<UEventPlayerPhaseView*>(TEXT("allPhases"), AllPhases, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("rankRewards"), RankRewards, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("scoreRewards"), ScoreRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPlayerPhaseView*>(TEXT("currentPhase"), &CurrentPhase, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPlayerGroupState*>(TEXT("groupRewards"), &GroupRewards, Serializer);		
}

void UEventPlayerStateView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("running"), Bag, bRunning);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rank"), Bag, Rank);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("score"), Bag, Score);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("secondsRemaining"), Bag, SecondsRemaining);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("leaderboardId"), Bag, LeaderboardId);
	UBeamJsonUtils::DeserializeArray<UEventPlayerPhaseView*>(TEXT("allPhases"), Bag, AllPhases, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(TEXT("rankRewards"), Bag, RankRewards, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(TEXT("scoreRewards"), Bag, ScoreRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UEventPlayerPhaseView*>("currentPhase", Bag, CurrentPhase, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UEventPlayerGroupState*>("groupRewards", Bag, GroupRewards, OuterOwner);
}



