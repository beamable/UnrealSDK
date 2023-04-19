
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetStatusForGroupsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("groupIds"), GroupIds, Serializer);
}

void UGetStatusForGroupsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("groupIds"), GroupIds, Serializer);		
}

void UGetStatusForGroupsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ContentId = Bag->GetStringField(TEXT("contentId"));
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("groupIds")), GroupIds, OuterOwner);
}



