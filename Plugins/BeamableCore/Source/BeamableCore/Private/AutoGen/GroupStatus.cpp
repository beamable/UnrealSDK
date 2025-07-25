
#include "BeamableCore/Public/AutoGen/GroupStatus.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGroupStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastUpdateCycle"), LastUpdateCycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groupId"), GroupId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCompletedStatus*>, UCompletedStatus*>(TEXT("completed"), &Completed, Serializer);
}

void UGroupStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastUpdateCycle"), LastUpdateCycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groupId"), GroupId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCompletedStatus*>, UCompletedStatus*>(TEXT("completed"), &Completed, Serializer);		
}

void UGroupStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lastUpdateCycle"), Bag, LastUpdateCycle);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tournamentId"), Bag, TournamentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("stage"), Bag, Stage);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tier"), Bag, Tier);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("groupId"), Bag, GroupId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeOptional<TArray<UCompletedStatus*>, UCompletedStatus*>("completed", Bag, Completed, OuterOwner);
}



