
#include "BeamableCore/Public/AutoGen/HtmlResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UHtmlResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UHtmlResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("html"), &Html, Serializer);
}

void UHtmlResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("html"), &Html, Serializer);		
}

void UHtmlResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("html", Bag, Html, OuterOwner);
}



