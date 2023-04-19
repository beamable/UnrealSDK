
#include "BeamableCore/Public/AutoGen/GroupStatus.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGroupStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lastUpdateCycle"), LastUpdateCycle);
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("groupId"), GroupId);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeOptional<TArray<UCompletedStatus*>, UCompletedStatus*>(TEXT("completed"), &Completed, Serializer);
}

void UGroupStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lastUpdateCycle"), LastUpdateCycle);
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("groupId"), GroupId);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeOptional<TArray<UCompletedStatus*>, UCompletedStatus*>(TEXT("completed"), &Completed, Serializer);		
}

void UGroupStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	LastUpdateCycle = Bag->GetIntegerField(TEXT("lastUpdateCycle"));
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	Stage = Bag->GetIntegerField(TEXT("stage"));
	Tier = Bag->GetIntegerField(TEXT("tier"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("groupId")), GroupId);
	ContentId = Bag->GetStringField(TEXT("contentId"));
	UBeamJsonUtils::DeserializeOptional<TArray<UCompletedStatus*>, UCompletedStatus*>("completed", Bag, Completed, OuterOwner);
}



