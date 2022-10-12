
#include "AutoGen/AnnouncementState.h"



void UAnnouncementState ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isRead"), bIsRead);
	Serializer->WriteValue(TEXT("isClaimed"), bIsClaimed);
	Serializer->WriteValue(TEXT("isDeleted"), bIsDeleted);
}

void UAnnouncementState::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isRead"), bIsRead);
	Serializer->WriteValue(TEXT("isClaimed"), bIsClaimed);
	Serializer->WriteValue(TEXT("isDeleted"), bIsDeleted);		
}

void UAnnouncementState ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bIsRead = Bag->GetBoolField(TEXT("isRead"));
	bIsClaimed = Bag->GetBoolField(TEXT("isClaimed"));
	bIsDeleted = Bag->GetBoolField(TEXT("isDeleted"));
}