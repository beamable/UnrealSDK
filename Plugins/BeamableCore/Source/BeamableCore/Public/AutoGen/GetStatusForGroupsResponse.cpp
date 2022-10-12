
#include "AutoGen/GetStatusForGroupsResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UGetStatusForGroupsResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGroupStatus*>(TEXT("statuses"), Statuses, Serializer);
	Serializer->WriteValue(TEXT("contentId"), ContentId);
}

void UGetStatusForGroupsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGroupStatus*>(TEXT("statuses"), Statuses, Serializer);
	Serializer->WriteValue(TEXT("contentId"), ContentId);		
}

void UGetStatusForGroupsResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UGroupStatus*>(Bag->GetArrayField(TEXT("statuses")), Statuses, OuterOwner);
	ContentId = Bag->GetStringField(TEXT("contentId"));
}