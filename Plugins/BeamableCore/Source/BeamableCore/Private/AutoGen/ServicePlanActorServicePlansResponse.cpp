
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlansResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UServicePlanActorServicePlansResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UServicePlanActorServicePlansResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UServicePlanActorServicePlan*>, UServicePlanActorServicePlan*>(TEXT("plans"), &Plans, Serializer);
}

void UServicePlanActorServicePlansResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UServicePlanActorServicePlan*>, UServicePlanActorServicePlan*>(TEXT("plans"), &Plans, Serializer);		
}

void UServicePlanActorServicePlansResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UServicePlanActorServicePlan*>, UServicePlanActorServicePlan*>("plans", Bag, Plans, OuterOwner);
}



