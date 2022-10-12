
#include "AutoGen/EventPlayerStateView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UEventPlayerStateView ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("running"), bRunning);
	UBeamJsonUtils::SerializeArray<UEventPlayerPhaseView*>(TEXT("allPhases"), AllPhases, Serializer);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeOptional<UEventPlayerPhaseView*>(TEXT("currentPhase"), &CurrentPhase, Serializer);
	Serializer->WriteValue(TEXT("secondsRemaining"), SecondsRemaining);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("rankRewards"), RankRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPlayerGroupState*>(TEXT("groupRewards"), &GroupRewards, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("scoreRewards"), ScoreRewards, Serializer);
}

void UEventPlayerStateView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("running"), bRunning);
	UBeamJsonUtils::SerializeArray<UEventPlayerPhaseView*>(TEXT("allPhases"), AllPhases, Serializer);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeOptional<UEventPlayerPhaseView*>(TEXT("currentPhase"), &CurrentPhase, Serializer);
	Serializer->WriteValue(TEXT("secondsRemaining"), SecondsRemaining);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("rankRewards"), RankRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPlayerGroupState*>(TEXT("groupRewards"), &GroupRewards, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("scoreRewards"), ScoreRewards, Serializer);		
}

void UEventPlayerStateView ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	bRunning = Bag->GetBoolField(TEXT("running"));
	UBeamJsonUtils::DeserializeArray<UEventPlayerPhaseView*>(Bag->GetArrayField(TEXT("allPhases")), AllPhases, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("rank")), Rank);
	Score = Bag->GetNumberField(TEXT("score"));
	UBeamJsonUtils::DeserializeOptional<UEventPlayerPhaseView*>("currentPhase", Bag, CurrentPhase, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("secondsRemaining")), SecondsRemaining);
	Id = Bag->GetStringField(TEXT("id"));
	LeaderboardId = Bag->GetStringField(TEXT("leaderboardId"));
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(Bag->GetArrayField(TEXT("rankRewards")), RankRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UEventPlayerGroupState*>("groupRewards", Bag, GroupRewards, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(Bag->GetArrayField(TEXT("scoreRewards")), ScoreRewards, OuterOwner);
}