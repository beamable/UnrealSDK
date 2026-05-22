
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterGroundItemResult.h"




void URegisterGroundItemResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URegisterGroundItemResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
}

void URegisterGroundItemResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);		
}

void URegisterGroundItemResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
}



