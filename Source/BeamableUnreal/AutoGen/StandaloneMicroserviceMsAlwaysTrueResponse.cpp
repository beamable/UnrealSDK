
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAlwaysTrueResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UStandaloneMicroserviceMsAlwaysTrueResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<bool>(ResponseContent, bValue, OuterOwner);
}

void UStandaloneMicroserviceMsAlwaysTrueResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);
}

void UStandaloneMicroserviceMsAlwaysTrueResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);		
}

void UStandaloneMicroserviceMsAlwaysTrueResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bValue = Bag->GetBoolField(TEXT("Value"));
}



