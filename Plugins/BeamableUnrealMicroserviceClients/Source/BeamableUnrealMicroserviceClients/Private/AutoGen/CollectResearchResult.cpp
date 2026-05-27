
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResearchResult.h"

#include "Misc/DefaultValueHelper.h"


void UCollectResearchResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCollectResearchResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("outputContentId"), OutputContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("outputQuantity"), OutputQuantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("outputType"), OutputType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
}

void UCollectResearchResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("outputContentId"), OutputContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("outputQuantity"), OutputQuantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("outputType"), OutputType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);		
}

void UCollectResearchResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("outputContentId"), Bag, OutputContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("outputQuantity"), Bag, OutputQuantity);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("outputType"), Bag, OutputType);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
}



