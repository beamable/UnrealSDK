
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isClaimed")), bIsClaimed);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isDeleted")), bIsDeleted);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isRead")), bIsRead);
}



