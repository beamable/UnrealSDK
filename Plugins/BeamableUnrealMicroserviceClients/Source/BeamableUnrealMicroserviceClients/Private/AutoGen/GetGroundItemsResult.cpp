
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetGroundItemsResult.h"
#include "Serialization/BeamJsonUtils.h"



void UGetGroundItemsResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetGroundItemsResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<UGroundItemEntry*>(TEXT("items"), Items, Serializer);
}

void UGetGroundItemsResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<UGroundItemEntry*>(TEXT("items"), Items, Serializer);		
}

void UGetGroundItemsResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
	UBeamJsonUtils::DeserializeArray<UGroundItemEntry*>(TEXT("items"), Bag, Items, OuterOwner);
}



