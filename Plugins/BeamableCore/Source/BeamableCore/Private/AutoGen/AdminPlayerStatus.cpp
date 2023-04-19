
#include "BeamableCore/Public/AutoGen/AdminPlayerStatus.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UAdminPlayerStatus::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAdminPlayerStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	Serializer->WriteValue(TEXT("nextCycleStartMs"), NextCycleStartMs);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);
}

void UAdminPlayerStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	Serializer->WriteValue(TEXT("nextCycleStartMs"), NextCycleStartMs);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);		
}

void UAdminPlayerStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	Stage = Bag->GetIntegerField(TEXT("stage"));
	Tier = Bag->GetIntegerField(TEXT("tier"));
	Rank = Bag->GetIntegerField(TEXT("rank"));
	Score = Bag->GetNumberField(TEXT("score"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	ContentId = Bag->GetStringField(TEXT("contentId"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("nextCycleStartMs")), NextCycleStartMs);
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(Bag->GetArrayField(TEXT("unclaimedRewards")), UnclaimedRewards, OuterOwner);
}



