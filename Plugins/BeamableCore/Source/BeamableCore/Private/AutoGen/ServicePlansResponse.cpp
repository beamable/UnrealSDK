
#include "BeamableCore/Public/AutoGen/ServicePlansResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UServicePlansResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UServicePlansResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UServicePlanActorServicePlan*>, UServicePlanActorServicePlan*>(TEXT("result"), &Result, Serializer);
}

void UServicePlansResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UServicePlanActorServicePlan*>, UServicePlanActorServicePlan*>(TEXT("result"), &Result, Serializer);		
}

void UServicePlansResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UServicePlanActorServicePlan*>, UServicePlanActorServicePlan*>("result", Bag, Result, OuterOwner);
}



