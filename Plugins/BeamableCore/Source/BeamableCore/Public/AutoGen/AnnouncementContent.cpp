
#include "AutoGen/AnnouncementContent.h"
#include "Serialization/BeamJsonUtils.h"


void UAnnouncementContent ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("channel"), Channel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start_date"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>(TEXT("stat_requirements"), &StatRequirements, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end_date"), &EndDate, Serializer);
	Serializer->WriteValue(TEXT("title"), Title);
	UBeamJsonUtils::SerializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>(TEXT("attachments"), &Attachments, Serializer);
	Serializer->WriteValue(TEXT("summary"), Summary);
}

void UAnnouncementContent::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("channel"), Channel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start_date"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>(TEXT("stat_requirements"), &StatRequirements, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end_date"), &EndDate, Serializer);
	Serializer->WriteValue(TEXT("title"), Title);
	UBeamJsonUtils::SerializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>(TEXT("attachments"), &Attachments, Serializer);
	Serializer->WriteValue(TEXT("summary"), Summary);		
}

void UAnnouncementContent ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Body = Bag->GetStringField(TEXT("body"));
	Channel = Bag->GetStringField(TEXT("channel"));
	UBeamJsonUtils::DeserializeOptional<FString>("start_date", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("gift", Bag, Gift, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>("stat_requirements", Bag, StatRequirements, OuterOwner);
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("clientData", Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("end_date", Bag, EndDate, OuterOwner);
	Title = Bag->GetStringField(TEXT("title"));
	UBeamJsonUtils::DeserializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>("attachments", Bag, Attachments, OuterOwner);
	Summary = Bag->GetStringField(TEXT("summary"));
}