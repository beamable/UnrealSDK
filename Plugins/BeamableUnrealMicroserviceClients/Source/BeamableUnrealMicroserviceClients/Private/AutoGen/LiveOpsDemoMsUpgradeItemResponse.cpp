
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsUpgradeItemResponse.h"
#include "Serialization/BeamJsonUtils.h"



void ULiveOpsDemoMsUpgradeItemResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<bool>(ResponseContent, bValue, OuterOwner);
}

void ULiveOpsDemoMsUpgradeItemResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);
}

void ULiveOpsDemoMsUpgradeItemResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);		
}

void ULiveOpsDemoMsUpgradeItemResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bValue = Bag->GetBoolField(TEXT("Value"));
}



