
#include "BeamableCore/Public/AutoGen/PlayerStatus.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UPlayerStatus::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPlayerStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lastUpdateCycle"), LastUpdateCycle);
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("groupId"), &GroupId, Serializer);
}

void UPlayerStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("lastUpdateCycle"), LastUpdateCycle);
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("groupId"), &GroupId, Serializer);		
}

void UPlayerStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	LastUpdateCycle = Bag->GetIntegerField(TEXT("lastUpdateCycle"));
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	Stage = Bag->GetIntegerField(TEXT("stage"));
	Tier = Bag->GetIntegerField(TEXT("tier"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	ContentId = Bag->GetStringField(TEXT("contentId"));
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(Bag->GetArrayField(TEXT("unclaimedRewards")), UnclaimedRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("groupId", Bag, GroupId, OuterOwner);
}



