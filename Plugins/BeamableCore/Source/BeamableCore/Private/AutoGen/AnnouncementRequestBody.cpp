
#include "BeamableCore/Public/AutoGen/AnnouncementRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAnnouncementRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("announcement"), &Announcement, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("announcements"), &Announcements, Serializer);
}

void UAnnouncementRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("announcement"), &Announcement, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("announcements"), &Announcements, Serializer);		
}

void UAnnouncementRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("announcement", Bag, Announcement, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("announcements", Bag, Announcements, OuterOwner);
}



