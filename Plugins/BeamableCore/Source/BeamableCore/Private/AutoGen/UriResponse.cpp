
#include "BeamableCore/Public/AutoGen/UriResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UUriResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UUriResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uri"), &Uri, Serializer);
}

void UUriResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uri"), &Uri, Serializer);		
}

void UUriResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("uri", Bag, Uri, OuterOwner);
}



