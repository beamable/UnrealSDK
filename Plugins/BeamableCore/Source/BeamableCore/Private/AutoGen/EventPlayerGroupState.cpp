
#include "BeamableCore/Public/AutoGen/EventPlayerGroupState.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPlayerGroupState::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("groupScore"), GroupScore);
	Serializer->WriteValue(TEXT("groupRank"), GroupRank);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("rankRewards"), RankRewards, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("scoreRewards"), ScoreRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);
}

void UEventPlayerGroupState::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("groupScore"), GroupScore);
	Serializer->WriteValue(TEXT("groupRank"), GroupRank);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("rankRewards"), RankRewards, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRewardState*>(TEXT("scoreRewards"), ScoreRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("groupId"), &GroupId, Serializer);		
}

void UEventPlayerGroupState::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	GroupScore = Bag->GetNumberField(TEXT("groupScore"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("groupRank")), GroupRank);
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(Bag->GetArrayField(TEXT("rankRewards")), RankRewards, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEventRewardState*>(Bag->GetArrayField(TEXT("scoreRewards")), ScoreRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("groupId", Bag, GroupId, OuterOwner);
}



