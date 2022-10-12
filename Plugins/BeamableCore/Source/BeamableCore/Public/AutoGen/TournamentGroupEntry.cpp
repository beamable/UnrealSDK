
#include "AutoGen/TournamentGroupEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UTournamentGroupEntry ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);
	Serializer->WriteValue(TEXT("groupId"), GroupId);
	Serializer->WriteValue(TEXT("stageChange"), StageChange);
}

void UTournamentGroupEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);
	Serializer->WriteValue(TEXT("groupId"), GroupId);
	Serializer->WriteValue(TEXT("stageChange"), StageChange);		
}

void UTournamentGroupEntry ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("rank")), Rank);
	Score = Bag->GetNumberField(TEXT("score"));
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(Bag->GetArrayField(TEXT("currencyRewards")), CurrencyRewards, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("groupId")), GroupId);
	StageChange = Bag->GetIntegerField(TEXT("stageChange"));
}