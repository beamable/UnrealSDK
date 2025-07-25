
#include "BeamableCore/Public/AutoGen/TournamentGroupEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UTournamentGroupEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groupId"), GroupId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stageChange"), StageChange, Serializer);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);
}

void UTournamentGroupEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groupId"), GroupId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stageChange"), StageChange, Serializer);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);		
}

void UTournamentGroupEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rank"), Bag, Rank);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("score"), Bag, Score);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("groupId"), Bag, GroupId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("stageChange"), Bag, StageChange);
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), Bag, CurrencyRewards, OuterOwner);
}



