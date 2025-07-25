
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetStatusForGroupsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetStatusForGroupsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeArray<UGroupStatus*>(TEXT("statuses"), Statuses, Serializer);
}

void UGetStatusForGroupsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeArray<UGroupStatus*>(TEXT("statuses"), Statuses, Serializer);		
}

void UGetStatusForGroupsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeArray<UGroupStatus*>(TEXT("statuses"), Bag, Statuses, OuterOwner);
}



