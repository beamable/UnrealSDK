
#include "BeamableCore/Public/AutoGen/ArchetypeProxy.h"





void UArchetypeProxy::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("namespace"), Namespace);
}

void UArchetypeProxy::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("namespace"), Namespace);		
}

void UArchetypeProxy::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Service = Bag->GetStringField(TEXT("service"));
	Namespace = Bag->GetStringField(TEXT("namespace"));
}



