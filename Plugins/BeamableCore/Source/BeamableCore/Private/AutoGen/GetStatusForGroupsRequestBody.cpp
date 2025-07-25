
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetStatusForGroupsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("groupIds"), GroupIds, Serializer);
}

void UGetStatusForGroupsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("groupIds"), GroupIds, Serializer);		
}

void UGetStatusForGroupsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeArray<int64>(TEXT("groupIds"), Bag, GroupIds, OuterOwner);
}



