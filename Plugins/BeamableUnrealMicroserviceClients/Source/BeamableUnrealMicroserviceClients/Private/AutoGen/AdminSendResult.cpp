
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AdminSendResult.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UAdminSendResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAdminSendResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("attempted"), Attempted, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("succeeded"), Succeeded, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("failed"), Failed, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("messages"), Messages, Serializer);
}

void UAdminSendResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("attempted"), Attempted, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("succeeded"), Succeeded, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("failed"), Failed, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("messages"), Messages, Serializer);		
}

void UAdminSendResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("attempted"), Bag, Attempted);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("succeeded"), Bag, Succeeded);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("failed"), Bag, Failed);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("messages"), Bag, Messages, OuterOwner);
}



