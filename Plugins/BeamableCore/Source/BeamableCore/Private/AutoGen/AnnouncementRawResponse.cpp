
#include "AutoGen/AnnouncementRawResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UAnnouncementRawResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<UAnnouncementState*>(TEXT("announcements"), Announcements, Serializer);
}

void UAnnouncementRawResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<UAnnouncementState*>(TEXT("announcements"), Announcements, Serializer);		
}

void UAnnouncementRawResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<UAnnouncementState*>(Bag->GetObjectField(TEXT("announcements")), Announcements, OuterOwner);
}