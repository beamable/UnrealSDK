
#include "AutoGen/ItemArchetype.h"
#include "Serialization/BeamJsonUtils.h"




void UItemArchetype ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<UInventoryProxySettings*>(TEXT("proxy"), &Proxy, Serializer);
	UBeamJsonUtils::SerializeOptional<UClientPermission*>(TEXT("clientPermission"), &ClientPermission, Serializer);
}

void UItemArchetype::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<UInventoryProxySettings*>(TEXT("proxy"), &Proxy, Serializer);
	UBeamJsonUtils::SerializeOptional<UClientPermission*>(TEXT("clientPermission"), &ClientPermission, Serializer);		
}

void UItemArchetype ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeOptional<UInventoryProxySettings*>("proxy", Bag, Proxy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UClientPermission*>("clientPermission", Bag, ClientPermission, OuterOwner);
}