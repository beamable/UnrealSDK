
#include "BeamableCore/Public/AutoGen/TournamentGroupEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UTournamentGroupEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("groupId"), GroupId);
	Serializer->WriteValue(TEXT("stageChange"), StageChange);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);
}

void UTournamentGroupEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("groupId"), GroupId);
	Serializer->WriteValue(TEXT("stageChange"), StageChange);
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("currencyRewards"), CurrencyRewards, Serializer);		
}

void UTournamentGroupEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("rank")), Rank);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("score")), Score);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("groupId")), GroupId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("stageChange")), StageChange);
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(Bag->GetArrayField(TEXT("currencyRewards")), CurrencyRewards, OuterOwner);
}



