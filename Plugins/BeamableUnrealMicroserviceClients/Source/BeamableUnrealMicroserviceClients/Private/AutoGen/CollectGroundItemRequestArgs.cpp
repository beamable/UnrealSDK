
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectGroundItemRequestArgs.h"





void UCollectGroundItemRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groundItemId"), GroundItemId, Serializer);
}

void UCollectGroundItemRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("groundItemId"), GroundItemId, Serializer);		
}

void UCollectGroundItemRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("groundItemId"), Bag, GroundItemId);
}



