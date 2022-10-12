
#include "AutoGen/AnnouncementView.h"
#include "Serialization/BeamJsonUtils.h"


void UAnnouncementView ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("isClaimed"), bIsClaimed);
	Serializer->WriteValue(TEXT("channel"), Channel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemaining"), &SecondsRemaining, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("isDeleted"), bIsDeleted);
	Serializer->WriteValue(TEXT("isRead"), bIsRead);
	Serializer->WriteValue(TEXT("title"), Title);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeArray<UAnnouncementAttachment*>(TEXT("attachments"), Attachments, Serializer);
	Serializer->WriteValue(TEXT("summary"), Summary);
}

void UAnnouncementView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("isClaimed"), bIsClaimed);
	Serializer->WriteValue(TEXT("channel"), Channel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("endDate"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemaining"), &SecondsRemaining, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("isDeleted"), bIsDeleted);
	Serializer->WriteValue(TEXT("isRead"), bIsRead);
	Serializer->WriteValue(TEXT("title"), Title);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("startDate"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeArray<UAnnouncementAttachment*>(TEXT("attachments"), Attachments, Serializer);
	Serializer->WriteValue(TEXT("summary"), Summary);		
}

void UAnnouncementView ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Body = Bag->GetStringField(TEXT("body"));
	bIsClaimed = Bag->GetBoolField(TEXT("isClaimed"));
	Channel = Bag->GetStringField(TEXT("channel"));
	UBeamJsonUtils::DeserializeOptional<FString>("endDate", Bag, EndDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UClientDataEntry*>(Bag->GetArrayField(TEXT("clientDataList")), ClientDataList, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("gift", Bag, Gift, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemaining", Bag, SecondsRemaining, OuterOwner);
	Id = Bag->GetStringField(TEXT("id"));
	bIsDeleted = Bag->GetBoolField(TEXT("isDeleted"));
	bIsRead = Bag->GetBoolField(TEXT("isRead"));
	Title = Bag->GetStringField(TEXT("title"));
	UBeamJsonUtils::DeserializeOptional<FString>("startDate", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UAnnouncementAttachment*>(Bag->GetArrayField(TEXT("attachments")), Attachments, OuterOwner);
	Summary = Bag->GetStringField(TEXT("summary"));
}