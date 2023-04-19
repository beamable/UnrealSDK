
#include "BeamableCore/Public/AutoGen/TournamentCurrencyReward.h"

#include "Misc/DefaultValueHelper.h"



void UTournamentCurrencyReward::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("amount"), Amount);
}

void UTournamentCurrencyReward::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("amount"), Amount);		
}

void UTournamentCurrencyReward::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
}



