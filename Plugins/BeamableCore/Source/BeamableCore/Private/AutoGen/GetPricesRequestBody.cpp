
#include "BeamableCore/Public/AutoGen/GetPricesRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UGetPricesRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("steamId"), SteamId, Serializer);
}

void UGetPricesRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("steamId"), SteamId, Serializer);		
}

void UGetPricesRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("steamId"), Bag, SteamId);
}



