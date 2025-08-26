
#include "BeamableCore/Public/AutoGen/GetSignedUrlResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetSignedUrlResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetSignedUrlResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("url"), Url, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("method"), Method, Serializer);
	UBeamJsonUtils::SerializeArray<UGetLogsUrlHeader*>(TEXT("headers"), Headers, Serializer);
}

void UGetSignedUrlResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("url"), Url, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("method"), Method, Serializer);
	UBeamJsonUtils::SerializeArray<UGetLogsUrlHeader*>(TEXT("headers"), Headers, Serializer);		
}

void UGetSignedUrlResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("url"), Bag, Url);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("body"), Bag, Body);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("method"), Bag, Method);
	UBeamJsonUtils::DeserializeArray<UGetLogsUrlHeader*>(TEXT("headers"), Bag, Headers, OuterOwner);
}



