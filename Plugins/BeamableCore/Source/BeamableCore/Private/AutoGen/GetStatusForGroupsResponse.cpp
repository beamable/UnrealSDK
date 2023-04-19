
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetStatusForGroupsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetStatusForGroupsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeArray<UGroupStatus*>(TEXT("statuses"), Statuses, Serializer);
}

void UGetStatusForGroupsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentId"), ContentId);
	UBeamJsonUtils::SerializeArray<UGroupStatus*>(TEXT("statuses"), Statuses, Serializer);		
}

void UGetStatusForGroupsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ContentId = Bag->GetStringField(TEXT("contentId"));
	UBeamJsonUtils::DeserializeArray<UGroupStatus*>(Bag->GetArrayField(TEXT("statuses")), Statuses, OuterOwner);
}



