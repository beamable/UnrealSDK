
#include "BeamableCore/Public/AutoGen/AnnouncementQueryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAnnouncementQueryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAnnouncementQueryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAnnouncementView*>(TEXT("announcements"), Announcements, Serializer);
}

void UAnnouncementQueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAnnouncementView*>(TEXT("announcements"), Announcements, Serializer);		
}

void UAnnouncementQueryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UAnnouncementView*>(Bag->GetArrayField(TEXT("announcements")), Announcements, OuterOwner);
}



