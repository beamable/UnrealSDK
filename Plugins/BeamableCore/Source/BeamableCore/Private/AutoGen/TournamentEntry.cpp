
#include "BeamableCore/Public/AutoGen/TournamentEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UTournamentEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("stageChange"), StageChange);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("previousStageChange"), &PreviousStageChange, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("nextStageChange"), &NextStageChange, Serializer);
}

void UTournamentEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("stage"), Stage);
	Serializer->WriteValue(TEXT("tier"), Tier);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("stageChange"), StageChange);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("previousStageChange"), &PreviousStageChange, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("nextStageChange"), &NextStageChange, Serializer);		
}

void UTournamentEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("stage")), Stage);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("tier")), Tier);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("rank")), Rank);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("score")), Score);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("stageChange")), StageChange);
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(Bag->GetArrayField(TEXT("currencyRewards")), CurrencyRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("previousStageChange", Bag, PreviousStageChange, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("nextStageChange", Bag, NextStageChange, OuterOwner);
}



