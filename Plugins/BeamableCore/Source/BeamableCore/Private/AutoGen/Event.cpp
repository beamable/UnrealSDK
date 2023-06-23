
#include "BeamableCore/Public/AutoGen/Event.h"
#include "Serialization/BeamJsonUtils.h"




void UEvent::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("start_date"), StartDate);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<UEventPhase*>(TEXT("phases"), Phases, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("partition_size"), &PartitionSize, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventGroupRewards*>(TEXT("group_rewards"), &GroupRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<USchedule*>(TEXT("schedule"), &Schedule, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("stores"), &Stores, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardContent*>, UEventRewardContent*>(TEXT("score_rewards"), &ScoreRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardContent*>, UEventRewardContent*>(TEXT("rank_rewards"), &RankRewards, Serializer);
}

void UEvent::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("start_date"), StartDate);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<UEventPhase*>(TEXT("phases"), Phases, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("partition_size"), &PartitionSize, Serializer);
	UBeamJsonUtils::SerializeOptional<UEventGroupRewards*>(TEXT("group_rewards"), &GroupRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<ULeaderboardCohortSettings*>(TEXT("cohortSettings"), &CohortSettings, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("permissions"), &Permissions, Serializer);
	UBeamJsonUtils::SerializeOptional<USchedule*>(TEXT("schedule"), &Schedule, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("stores"), &Stores, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardContent*>, UEventRewardContent*>(TEXT("score_rewards"), &ScoreRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardContent*>, UEventRewardContent*>(TEXT("rank_rewards"), &RankRewards, Serializer);		
}

void UEvent::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	StartDate = Bag->GetStringField(TEXT("start_date"));
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeArray<UEventPhase*>(Bag->GetArrayField(TEXT("phases")), Phases, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("partition_size", Bag, PartitionSize, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UEventGroupRewards*>("group_rewards", Bag, GroupRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<ULeaderboardCohortSettings*>("cohortSettings", Bag, CohortSettings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamClientPermission>("permissions", Bag, Permissions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USchedule*>("schedule", Bag, Schedule, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("stores", Bag, Stores, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRewardContent*>, UEventRewardContent*>("score_rewards", Bag, ScoreRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRewardContent*>, UEventRewardContent*>("rank_rewards", Bag, RankRewards, OuterOwner);
}



