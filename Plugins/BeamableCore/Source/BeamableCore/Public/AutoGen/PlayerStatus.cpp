
#include "AutoGen/PlayerStatus.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UPlayerStatus ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lastUpdateCycle"), LastUpdateCycle);
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("stage"), Stage);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);
	Serializer->WriteValue(TEXT("tier"), Tier);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("groupId"), &GroupId, Serializer);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
}

void UPlayerStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lastUpdateCycle"), LastUpdateCycle);
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("stage"), Stage);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);
	Serializer->WriteValue(TEXT("tier"), Tier);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("groupId"), &GroupId, Serializer);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("contentId"), ContentId);		
}

void UPlayerStatus ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	LastUpdateCycle = Bag->GetIntegerField(TEXT("lastUpdateCycle"));
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	Stage = Bag->GetIntegerField(TEXT("stage"));
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(Bag->GetArrayField(TEXT("unclaimedRewards")), UnclaimedRewards, OuterOwner);
	Tier = Bag->GetIntegerField(TEXT("tier"));
	UBeamJsonUtils::DeserializeOptional<int64>("groupId", Bag, GroupId, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	ContentId = Bag->GetStringField(TEXT("contentId"));
}