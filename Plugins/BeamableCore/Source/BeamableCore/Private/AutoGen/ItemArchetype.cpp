
#include "BeamableCore/Public/AutoGen/ItemArchetype.h"
#include "Serialization/BeamJsonUtils.h"




void UItemArchetype::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("clientPermission"), &ClientPermission, Serializer);
}

void UItemArchetype::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("clientPermission"), &ClientPermission, Serializer);		
}

void UItemArchetype::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeOptional<UFederationInfo*>("external", Bag, External, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamClientPermission>("clientPermission", Bag, ClientPermission, OuterOwner);
}



