
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectGroundItemResult.h"

#include "Misc/DefaultValueHelper.h"


void UCollectGroundItemResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCollectGroundItemResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("grantedContentId"), GrantedContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("grantedQuantity"), GrantedQuantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
}

void UCollectGroundItemResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("grantedContentId"), GrantedContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("grantedQuantity"), GrantedQuantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);		
}

void UCollectGroundItemResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("grantedContentId"), Bag, GrantedContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("grantedQuantity"), Bag, GrantedQuantity);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
}



