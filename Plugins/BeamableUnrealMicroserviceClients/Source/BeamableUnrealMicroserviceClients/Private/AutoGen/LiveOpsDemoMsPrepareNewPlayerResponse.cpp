
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsPrepareNewPlayerResponse.h"
#include "Serialization/BeamJsonUtils.h"



void ULiveOpsDemoMsPrepareNewPlayerResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<bool>(ResponseContent, bValue, OuterOwner);
}

void ULiveOpsDemoMsPrepareNewPlayerResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);
}

void ULiveOpsDemoMsPrepareNewPlayerResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);		
}

void ULiveOpsDemoMsPrepareNewPlayerResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bValue = Bag->GetBoolField(TEXT("Value"));
}



