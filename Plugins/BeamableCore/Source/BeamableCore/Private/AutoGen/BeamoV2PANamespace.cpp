
#include "BeamableCore/Public/AutoGen/BeamoV2PANamespace.h"





void UBeamoV2PANamespace::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);
}

void UBeamoV2PANamespace::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("namespace"), Namespace, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);		
}

void UBeamoV2PANamespace::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("namespace")), Namespace);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);
}



