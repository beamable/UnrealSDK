
#include "BeamableCore/Public/AutoGen/InventoryUpdateDelta.h"
#include "Serialization/BeamJsonUtils.h"




void UInventoryUpdateDelta::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UItemDeltas*>("items", Items, Serializer);
	UBeamJsonUtils::SerializeMap<UCurrencyDelta*>(TEXT("currencies"), Currencies, Serializer);
}

void UInventoryUpdateDelta::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UItemDeltas*>("items", Items, Serializer);
	UBeamJsonUtils::SerializeMap<UCurrencyDelta*>(TEXT("currencies"), Currencies, Serializer);		
}

void UInventoryUpdateDelta::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UItemDeltas*>("items", Bag, Items, OuterOwner);
	UBeamJsonUtils::DeserializeMap<UCurrencyDelta*>(TEXT("currencies"), Bag, Currencies, OuterOwner);
}



