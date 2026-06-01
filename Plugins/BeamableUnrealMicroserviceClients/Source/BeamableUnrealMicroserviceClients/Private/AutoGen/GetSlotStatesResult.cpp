
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSlotStatesResult.h"
#include "Serialization/BeamJsonUtils.h"



void UGetSlotStatesResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetSlotStatesResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<USlotStateEntry*>(TEXT("slots"), Slots, Serializer);
}

void UGetSlotStatesResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<USlotStateEntry*>(TEXT("slots"), Slots, Serializer);		
}

void UGetSlotStatesResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
	UBeamJsonUtils::DeserializeArray<USlotStateEntry*>(TEXT("slots"), Bag, Slots, OuterOwner);
}



