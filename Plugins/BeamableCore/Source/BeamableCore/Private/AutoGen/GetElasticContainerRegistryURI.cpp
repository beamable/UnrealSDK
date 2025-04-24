
#include "BeamableCore/Public/AutoGen/GetElasticContainerRegistryURI.h"




void UGetElasticContainerRegistryURI::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetElasticContainerRegistryURI::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);
}

void UGetElasticContainerRegistryURI::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("uri"), Uri, Serializer);		
}

void UGetElasticContainerRegistryURI::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("uri")), Uri);
}



