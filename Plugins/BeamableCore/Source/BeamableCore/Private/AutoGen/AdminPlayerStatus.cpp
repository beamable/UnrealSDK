
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
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("nextCycleStartMs"), NextCycleStartMs, Serializer);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);
}

void UAdminPlayerStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("nextCycleStartMs"), NextCycleStartMs, Serializer);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);		
}

void UAdminPlayerStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tournamentId"), Bag, TournamentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("stage"), Bag, Stage);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tier"), Bag, Tier);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rank"), Bag, Rank);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("score"), Bag, Score);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("nextCycleStartMs"), Bag, NextCycleStartMs);
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), Bag, UnclaimedRewards, OuterOwner);
}



