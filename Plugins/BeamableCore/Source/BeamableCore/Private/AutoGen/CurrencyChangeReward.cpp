
#include "BeamableCore/Public/AutoGen/CurrencyChangeReward.h"

#include "Misc/DefaultValueHelper.h"



void UCurrencyChangeReward::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
}

void UCurrencyChangeReward::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);		
}

void UCurrencyChangeReward::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("symbol"), Bag, Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("amount"), Bag, Amount);
}



