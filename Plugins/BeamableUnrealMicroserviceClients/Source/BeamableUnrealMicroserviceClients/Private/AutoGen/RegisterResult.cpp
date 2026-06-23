
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterResult.h"

#include "Misc/DefaultValueHelper.h"


void URegisterResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URegisterResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deviceCount"), DeviceCount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
}

void URegisterResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deviceCount"), DeviceCount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);		
}

void URegisterResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("deviceCount"), Bag, DeviceCount);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
}



