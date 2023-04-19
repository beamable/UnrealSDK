
#include "BeamableCore/Public/AutoGen/ServicePlansResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UServicePlansResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UServicePlansResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServicePlan*>(TEXT("result"), Result, Serializer);
}

void UServicePlansResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServicePlan*>(TEXT("result"), Result, Serializer);		
}

void UServicePlansResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UServicePlan*>(Bag->GetArrayField(TEXT("result")), Result, OuterOwner);
}



