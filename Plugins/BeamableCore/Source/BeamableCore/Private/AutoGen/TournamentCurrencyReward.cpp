
#include "BeamableCore/Public/AutoGen/TournamentCurrencyReward.h"

#include "Misc/DefaultValueHelper.h"



void UTournamentCurrencyReward::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
}

void UTournamentCurrencyReward::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);		
}

void UTournamentCurrencyReward::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("symbol"), Bag, Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("amount"), Bag, Amount);
}



