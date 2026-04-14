
#include "BeamableCore/Public/AutoGen/RealmsBasicServicePlansResponse.h"
#include "Serialization/BeamJsonUtils.h"



void URealmsBasicServicePlansResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URealmsBasicServicePlansResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URealmsBasicServicePlan*>(TEXT("result"), Result, Serializer);
}

void URealmsBasicServicePlansResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<URealmsBasicServicePlan*>(TEXT("result"), Result, Serializer);		
}

void URealmsBasicServicePlansResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<URealmsBasicServicePlan*>(TEXT("result"), Bag, Result, OuterOwner);
}



