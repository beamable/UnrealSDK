
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UpgradeItemRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UUpgradeItemRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstaceID"), ItemInstaceID, Serializer);
}

void UUpgradeItemRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstaceID"), ItemInstaceID, Serializer);		
}

void UUpgradeItemRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gamerTag"), Bag, GamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemInstaceID"), Bag, ItemInstaceID);
}



