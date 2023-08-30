
#include "BeamableCore/Public/AutoGen/ItemArchetype.h"
#include "Serialization/BeamJsonUtils.h"




void UItemArchetype::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<UArchetypeProxy*>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("clientPermission"), &ClientPermission, Serializer);
}

void UItemArchetype::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<UArchetypeProxy*>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamClientPermission>(TEXT("clientPermission"), &ClientPermission, Serializer);		
}

void UItemArchetype::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeOptional<UArchetypeProxy*>("external", Bag, External, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamClientPermission>("clientPermission", Bag, ClientPermission, OuterOwner);
}



