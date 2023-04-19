
#include "BeamableCore/Public/AutoGen/CurrencyChangeReward.h"

#include "Misc/DefaultValueHelper.h"



void UCurrencyChangeReward::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("amount"), Amount);
}

void UCurrencyChangeReward::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("amount"), Amount);		
}

void UCurrencyChangeReward::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
}



