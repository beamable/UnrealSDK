
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterGroundItemRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void URegisterGroundItemRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groundItemId"), GroundItemId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("quantity"), Quantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemType"), ItemType, Serializer);
}

void URegisterGroundItemRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groundItemId"), GroundItemId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("quantity"), Quantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemType"), ItemType, Serializer);		
}

void URegisterGroundItemRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("groundItemId"), Bag, GroundItemId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("quantity"), Bag, Quantity);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemType"), Bag, ItemType);
}



