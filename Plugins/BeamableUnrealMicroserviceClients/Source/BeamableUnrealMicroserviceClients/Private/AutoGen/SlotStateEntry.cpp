
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SlotStateEntry.h"

#include "Misc/DefaultValueHelper.h"



void USlotStateEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slotId"), SlotId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("seedId"), SeedId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("harvestId"), HarvestId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("plantedAt"), PlantedAt, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("growSecs"), GrowSecs, Serializer);
}

void USlotStateEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slotId"), SlotId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("seedId"), SeedId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("harvestId"), HarvestId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("plantedAt"), PlantedAt, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("growSecs"), GrowSecs, Serializer);		
}

void USlotStateEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("slotId"), Bag, SlotId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("seedId"), Bag, SeedId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("harvestId"), Bag, HarvestId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("plantedAt"), Bag, PlantedAt);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("growSecs"), Bag, GrowSecs);
}



