
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
	Namespace = Bag->GetStringField(TEXT("namespace"));
	Type = Bag->GetStringField(TEXT("type"));
}



