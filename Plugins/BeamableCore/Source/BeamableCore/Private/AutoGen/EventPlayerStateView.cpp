
#include "BeamableCore/Public/AutoGen/EventPlayerStateView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPlayerStateView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("running"), bRunning);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("secondsRemaining"), SecondsRemaining);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
	UBeamJsonUtils::SerializeArray<UEventPlayerPhaseView*>(TEXT("allPhases"), AllPhases, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("rankRewards"), RankRewards, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("scoreRewards"), ScoreRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPlayerPhaseView*>(TEXT("currentPhase"), &CurrentPhase, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventPlayerGroupState*>(TEXT("groupRewards"), &GroupRewards, Serializer);
}

void UEventPlayerStateView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("running"), bRunning);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("secondsRemaining"), SecondsRemaining);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
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



