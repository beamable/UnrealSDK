
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GroundItemEntry.h"

#include "Misc/DefaultValueHelper.h"



void UGroundItemEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groundItemId"), GroundItemId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("quantity"), Quantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemType"), ItemType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("posX"), PosX, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("posY"), PosY, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("posZ"), PosZ, Serializer);
}

void UGroundItemEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groundItemId"), GroundItemId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("quantity"), Quantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemType"), ItemType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("posX"), PosX, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("posY"), PosY, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("posZ"), PosZ, Serializer);		
}

void UGroundItemEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("groundItemId"), Bag, GroundItemId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("quantity"), Bag, Quantity);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemType"), Bag, ItemType);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("posX"), Bag, PosX);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("posY"), Bag, PosY);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("posZ"), Bag, PosZ);
}



