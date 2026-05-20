
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutationResult.h"
#include "Serialization/BeamJsonUtils.h"



void UMutationResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMutationResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<UMutationOutput*>(TEXT("outputs"), Outputs, Serializer);
}

void UMutationResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeArray<UMutationOutput*>(TEXT("outputs"), Outputs, Serializer);		
}

void UMutationResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
	UBeamJsonUtils::DeserializeArray<UMutationOutput*>(TEXT("outputs"), Bag, Outputs, OuterOwner);
}



