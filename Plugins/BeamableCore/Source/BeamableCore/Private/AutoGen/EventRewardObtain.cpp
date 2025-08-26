
#include "BeamableCore/Public/AutoGen/EventRewardObtain.h"

#include "Misc/DefaultValueHelper.h"



void UEventRewardObtain::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("count"), Count, Serializer);
}

void UEventRewardObtain::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("count"), Count, Serializer);		
}

void UEventRewardObtain::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("symbol"), Bag, Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("count"), Bag, Count);
}



