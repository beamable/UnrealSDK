
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsIncrementStatResponse.h"
#include "Serialization/BeamJsonUtils.h"



void ULiveOpsDemoMsIncrementStatResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<bool>(ResponseContent, bValue, OuterOwner);
}

void ULiveOpsDemoMsIncrementStatResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);
}

void ULiveOpsDemoMsIncrementStatResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);		
}

void ULiveOpsDemoMsIncrementStatResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bValue = Bag->GetBoolField(TEXT("Value"));
}



