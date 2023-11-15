
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
	Serializer->WriteValue(TEXT("statusCode"), StatusCode);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
}

void ULambdaResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("statusCode"), StatusCode);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);		
}

void ULambdaResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	StatusCode = Bag->GetIntegerField(TEXT("statusCode"));
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
}



