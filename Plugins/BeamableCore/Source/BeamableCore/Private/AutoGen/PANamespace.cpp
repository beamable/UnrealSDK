
#include "BeamableCore/Public/AutoGen/PANamespace.h"





void UPANamespace::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	Serializer->WriteValue(TEXT("type"), Type);
}

void UPANamespace::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("namespace"), Namespace);
	Serializer->WriteValue(TEXT("type"), Type);		
}

void UPANamespace::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("namespace")), Namespace);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);
}



