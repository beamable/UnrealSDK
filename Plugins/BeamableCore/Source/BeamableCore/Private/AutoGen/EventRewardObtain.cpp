
#include "BeamableCore/Public/AutoGen/EventRewardObtain.h"

#include "Misc/DefaultValueHelper.h"



void UEventRewardObtain::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("count"), Count);
}

void UEventRewardObtain::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("count"), Count);		
}

void UEventRewardObtain::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	Count = Bag->GetIntegerField(TEXT("count"));
}



