
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SetEdgegapLocationRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void USetEdgegapLocationRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("latitude"), Latitude, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("longitude"), Longitude, Serializer);
}

void USetEdgegapLocationRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("latitude"), Latitude, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("longitude"), Longitude, Serializer);		
}

void USetEdgegapLocationRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("latitude"), Bag, Latitude);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("longitude"), Bag, Longitude);
}



