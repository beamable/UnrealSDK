
#include "BeamableCore/Public/AutoGen/GetServiceURLsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetServiceURLsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServiceImageLayers*>(TEXT("requests"), Requests, Serializer);
}

void UGetServiceURLsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServiceImageLayers*>(TEXT("requests"), Requests, Serializer);		
}

void UGetServiceURLsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UServiceImageLayers*>(Bag->GetArrayField(TEXT("requests")), Requests, OuterOwner);
}



