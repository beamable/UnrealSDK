
#include "AutoGen/GetStatusForGroupsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void UGetStatusForGroupsRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int64>(TEXT("groupIds"), GroupIds, Serializer);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
}

void UGetStatusForGroupsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int64>(TEXT("groupIds"), GroupIds, Serializer);
	Serializer->WriteValue(TEXT("contentId"), ContentId);		
}

void UGetStatusForGroupsRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("groupIds")), GroupIds, OuterOwner);
	ContentId = Bag->GetStringField(TEXT("contentId"));
}