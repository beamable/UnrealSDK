
#include "AutoGen/GetElasticContainerRegistryURI.h"



void UGetElasticContainerRegistryURI ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uri"), Uri);
}

void UGetElasticContainerRegistryURI::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("uri"), Uri);		
}

void UGetElasticContainerRegistryURI ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Uri = Bag->GetStringField(TEXT("uri"));
}