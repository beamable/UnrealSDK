
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSPrepareNewPlayerResponse.h"
#include "Serialization/BeamJsonUtils.h"



void ULiveOpsDemoMSPrepareNewPlayerResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<bool>(ResponseContent, bValue, OuterOwner);
}

void ULiveOpsDemoMSPrepareNewPlayerResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);
}

void ULiveOpsDemoMSPrepareNewPlayerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);		
}

void ULiveOpsDemoMSPrepareNewPlayerResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bValue = Bag->GetBoolField(TEXT("Value"));
}



