
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PushOffer.h"





void UPushOffer::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemId"), ItemId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customData"), CustomData, Serializer);
}

void UPushOffer::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemId"), ItemId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("customData"), CustomData, Serializer);		
}

void UPushOffer::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemId"), Bag, ItemId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("value"), Bag, Value);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("customData"), Bag, CustomData);
}



