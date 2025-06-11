
#include "BeamableCore/Public/AutoGen/AnnouncementState.h"





void UAnnouncementState::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isClaimed"), bIsClaimed, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isDeleted"), bIsDeleted, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isRead"), bIsRead, Serializer);
}

void UAnnouncementState::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isClaimed"), bIsClaimed, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isDeleted"), bIsDeleted, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isRead"), bIsRead, Serializer);		
}

void UAnnouncementState::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isClaimed")), bIsClaimed);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isDeleted")), bIsDeleted);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isRead")), bIsRead);
}



