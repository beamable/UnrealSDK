
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PlantSeedRequestArgs.h"





void UPlantSeedRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("seedContentId"), SeedContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slotId"), SlotId, Serializer);
}

void UPlantSeedRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("seedContentId"), SeedContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slotId"), SlotId, Serializer);		
}

void UPlantSeedRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("seedContentId"), Bag, SeedContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("slotId"), Bag, SlotId);
}



