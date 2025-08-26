
#include "BeamableCore/Public/AutoGen/TournamentEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UTournamentEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stageChange"), StageChange, Serializer);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("previousStageChange"), &PreviousStageChange, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("nextStageChange"), &NextStageChange, Serializer);
}

void UTournamentEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stage"), Stage, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tier"), Tier, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stageChange"), StageChange, Serializer);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("previousStageChange"), &PreviousStageChange, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("nextStageChange"), &NextStageChange, Serializer);		
}

void UTournamentEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("stage"), Bag, Stage);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tier"), Bag, Tier);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rank"), Bag, Rank);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("score"), Bag, Score);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("stageChange"), Bag, StageChange);
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), Bag, CurrencyRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("previousStageChange", Bag, PreviousStageChange, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("nextStageChange", Bag, NextStageChange, OuterOwner);
}



