
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetGroundItemsRequestArgs.h"





void UGetGroundItemsRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("spawnerId"), SpawnerId, Serializer);
}

void UGetGroundItemsRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("spawnerId"), SpawnerId, Serializer);		
}

void UGetGroundItemsRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("spawnerId"), Bag, SpawnerId);
}



