
#include "BeamableCore/Public/AutoGen/LambdaResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void ULambdaResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULambdaResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("statusCode"), StatusCode, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
}

void ULambdaResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("statusCode"), StatusCode, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);		
}

void ULambdaResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("statusCode")), StatusCode);
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
}



