
#include "AutoGen/ServicePlansResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UServicePlansResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServicePlan*>(TEXT("result"), Result, Serializer);
}

void UServicePlansResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServicePlan*>(TEXT("result"), Result, Serializer);		
}

void UServicePlansResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UServicePlan*>(Bag->GetArrayField(TEXT("result")), Result, OuterOwner);
}