
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSIncrementStatResponse.h"
#include "Serialization/BeamJsonUtils.h"



void ULiveOpsDemoMSIncrementStatResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<bool>(ResponseContent, bValue, OuterOwner);
}

void ULiveOpsDemoMSIncrementStatResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);
}

void ULiveOpsDemoMSIncrementStatResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);		
}

void ULiveOpsDemoMSIncrementStatResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bValue = Bag->GetBoolField(TEXT("Value"));
}



