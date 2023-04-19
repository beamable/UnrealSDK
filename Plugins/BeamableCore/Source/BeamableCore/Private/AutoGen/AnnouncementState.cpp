
#include "BeamableCore/Public/AutoGen/AnnouncementState.h"





void UAnnouncementState::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isClaimed"), bIsClaimed);
	Serializer->WriteValue(TEXT("isDeleted"), bIsDeleted);
	Serializer->WriteValue(TEXT("isRead"), bIsRead);
}

void UAnnouncementState::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isClaimed"), bIsClaimed);
	Serializer->WriteValue(TEXT("isDeleted"), bIsDeleted);
	Serializer->WriteValue(TEXT("isRead"), bIsRead);		
}

void UAnnouncementState::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bIsClaimed = Bag->GetBoolField(TEXT("isClaimed"));
	bIsDeleted = Bag->GetBoolField(TEXT("isDeleted"));
	bIsRead = Bag->GetBoolField(TEXT("isRead"));
}



