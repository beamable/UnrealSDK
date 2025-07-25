
#include "BeamableCore/Public/AutoGen/BeamoV2SignedRequestBody.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2SignedRequestBody::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2SignedRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("url"), &Url, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("method"), &Method, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2StringStringKeyValuePair*>, UBeamoV2StringStringKeyValuePair*>(TEXT("headers"), &Headers, Serializer);
}

void UBeamoV2SignedRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("url"), &Url, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("method"), &Method, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2StringStringKeyValuePair*>, UBeamoV2StringStringKeyValuePair*>(TEXT("headers"), &Headers, Serializer);		
}

void UBeamoV2SignedRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("url", Bag, Url, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("method", Bag, Method, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2StringStringKeyValuePair*>, UBeamoV2StringStringKeyValuePair*>("headers", Bag, Headers, OuterOwner);
}



