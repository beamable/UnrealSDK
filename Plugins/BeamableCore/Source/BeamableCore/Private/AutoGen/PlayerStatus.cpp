
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
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastUpdateCycle"), LastUpdateCycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("groupId"), &GroupId, Serializer);
}

void UPlayerStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("lastUpdateCycle"), LastUpdateCycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), UnclaimedRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("groupId"), &GroupId, Serializer);		
}

void UPlayerStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("lastUpdateCycle"), Bag, LastUpdateCycle);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tournamentId"), Bag, TournamentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("stage"), Bag, Stage);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tier"), Bag, Tier);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(TEXT("unclaimedRewards"), Bag, UnclaimedRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("groupId", Bag, GroupId, OuterOwner);
}



