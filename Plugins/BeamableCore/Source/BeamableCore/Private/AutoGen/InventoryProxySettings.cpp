
#include "AutoGen/InventoryProxySettings.h"
#include "Serialization/BeamJsonUtils.h"




void UInventoryProxySettings ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("namespace"), &Namespace, Serializer);
}

void UInventoryProxySettings::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("namespace"), &Namespace, Serializer);		
}

void UInventoryProxySettings ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Service = Bag->GetStringField(TEXT("service"));
	UBeamJsonUtils::DeserializeOptional<FString>("namespace", Bag, Namespace, OuterOwner);
}