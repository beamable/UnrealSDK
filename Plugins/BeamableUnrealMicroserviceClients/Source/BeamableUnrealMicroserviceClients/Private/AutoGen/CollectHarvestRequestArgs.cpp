
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectHarvestRequestArgs.h"





void UCollectHarvestRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slotId"), SlotId, Serializer);
}

void UCollectHarvestRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slotId"), SlotId, Serializer);		
}

void UCollectHarvestRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("slotId"), Bag, SlotId);
}



