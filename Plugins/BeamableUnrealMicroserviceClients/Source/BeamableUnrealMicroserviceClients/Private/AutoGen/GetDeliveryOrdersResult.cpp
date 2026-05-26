
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetDeliveryOrdersResult.h"
#include "Serialization/BeamJsonUtils.h"



void UGetDeliveryOrdersResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetDeliveryOrdersResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<UDeliveryOrderInfo*>(TEXT("orders"), Orders, Serializer);
}

void UGetDeliveryOrdersResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<UDeliveryOrderInfo*>(TEXT("orders"), Orders, Serializer);		
}

void UGetDeliveryOrdersResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
	UBeamJsonUtils::DeserializeArray<UDeliveryOrderInfo*>(TEXT("orders"), Bag, Orders, OuterOwner);
}



