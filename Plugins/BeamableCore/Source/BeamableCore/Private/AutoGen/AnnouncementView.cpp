
#include "BeamableCore/Public/AutoGen/AnnouncementView.h"
#include "Serialization/BeamJsonUtils.h"




void UAnnouncementView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isClaimed"), bIsClaimed, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isDeleted"), bIsDeleted, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isRead"), bIsRead, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("channel"), Channel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("summary"), Summary, Serializer);
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	UBeamJsonUtils::SerializeArray<UAnnouncementAttachment*>(TEXT("attachments"), Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemaining"), &SecondsRemaining, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
}

void UAnnouncementView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isClaimed"), bIsClaimed, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isDeleted"), bIsDeleted, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isRead"), bIsRead, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("channel"), Channel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("summary"), Summary, Serializer);
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	UBeamJsonUtils::SerializeArray<UAnnouncementAttachment*>(TEXT("attachments"), Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemaining"), &SecondsRemaining, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);		
}

void UAnnouncementView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isClaimed")), bIsClaimed);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isDeleted")), bIsDeleted);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isRead")), bIsRead);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("body")), Body);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("channel")), Channel);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("title")), Title);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("summary")), Summary);
	UBeamJsonUtils::DeserializeArray<UClientDataEntry*>(Bag->GetArrayField(TEXT("clientDataList")), ClientDataList, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UAnnouncementAttachment*>(Bag->GetArrayField(TEXT("attachments")), Attachments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("endDate", Bag, EndDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("gift", Bag, Gift, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemaining", Bag, SecondsRemaining, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("startDate", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
}



