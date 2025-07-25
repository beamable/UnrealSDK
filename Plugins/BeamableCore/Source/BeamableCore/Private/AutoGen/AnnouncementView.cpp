
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isClaimed"), Bag, bIsClaimed);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isDeleted"), Bag, bIsDeleted);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isRead"), Bag, bIsRead);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("body"), Bag, Body);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("channel"), Bag, Channel);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("title"), Bag, Title);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("summary"), Bag, Summary);
	UBeamJsonUtils::DeserializeArray<UClientDataEntry*>(TEXT("clientDataList"), Bag, ClientDataList, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UAnnouncementAttachment*>(TEXT("attachments"), Bag, Attachments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("endDate", Bag, EndDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("gift", Bag, Gift, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemaining", Bag, SecondsRemaining, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("startDate", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
}



