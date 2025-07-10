
#include "BeamableCore/Public/AutoGen/SignedRequestBody.h"
#include "Serialization/BeamJsonUtils.h"



void USignedRequestBody::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USignedRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("url"), &Url, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("method"), &Method, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UStringStringKeyValuePair*>, UStringStringKeyValuePair*>(TEXT("headers"), &Headers, Serializer);
}

void USignedRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("url"), &Url, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("method"), &Method, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UStringStringKeyValuePair*>, UStringStringKeyValuePair*>(TEXT("headers"), &Headers, Serializer);		
}

void USignedRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("url", Bag, Url, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("method", Bag, Method, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UStringStringKeyValuePair*>, UStringStringKeyValuePair*>("headers", Bag, Headers, OuterOwner);
}



