
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlan.h"
#include "Serialization/BeamJsonUtils.h"



void UServicePlanActorServicePlan::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UServicePlanActorServicePlan::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeUObject<UServicePlanActorDataDomain*>("dataDomain", DataDomain, Serializer);
	UBeamJsonUtils::SerializeOptional<UServicePlanActorServiceLimits*>(TEXT("serviceLimits"), &ServiceLimits, Serializer);
}

void UServicePlanActorServicePlan::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeUObject<UServicePlanActorDataDomain*>("dataDomain", DataDomain, Serializer);
	UBeamJsonUtils::SerializeOptional<UServicePlanActorServiceLimits*>(TEXT("serviceLimits"), &ServiceLimits, Serializer);		
}

void UServicePlanActorServicePlan::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeUObject<UServicePlanActorDataDomain*>("dataDomain", Bag, DataDomain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UServicePlanActorServiceLimits*>("serviceLimits", Bag, ServiceLimits, OuterOwner);
}



