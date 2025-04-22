
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("running")), bRunning);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("rank")), Rank);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("score")), Score);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("secondsRemaining")), SecondsRemaining);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("leaderboardId")), LeaderboardId);
	UBeamJsonUtils::DeserializeArray<UEventPlayerPhaseView*>(Bag->GetArrayField(TEXT("allPhases")), AllPhases, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(Bag->GetArrayField(TEXT("rankRewards")), RankRewards, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(Bag->GetArrayField(TEXT("scoreRewards")), ScoreRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UEventPlayerPhaseView*>("currentPhase", Bag, CurrentPhase, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UEventPlayerGroupState*>("groupRewards", Bag, GroupRewards, OuterOwner);
}



