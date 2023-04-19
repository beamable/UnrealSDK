
#include "BeamableCore/Public/AutoGen/AnnouncementContent.h"
#include "Serialization/BeamJsonUtils.h"




void UAnnouncementContent::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("channel"), Channel);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("title"), Title);
	Serializer->WriteValue(TEXT("summary"), Summary);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start_date"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end_date"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>(TEXT("stat_requirements"), &StatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>(TEXT("attachments"), &Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("clientData"), &ClientData, Serializer);
}

void UAnnouncementContent::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("channel"), Channel);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("title"), Title);
	Serializer->WriteValue(TEXT("summary"), Summary);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start_date"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end_date"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>(TEXT("stat_requirements"), &StatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>(TEXT("attachments"), &Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("clientData"), &ClientData, Serializer);		
}

void UAnnouncementContent::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Body = Bag->GetStringField(TEXT("body"));
	Channel = Bag->GetStringField(TEXT("channel"));
	Symbol = Bag->GetStringField(TEXT("symbol"));
	Title = Bag->GetStringField(TEXT("title"));
	Summary = Bag->GetStringField(TEXT("summary"));
	UBeamJsonUtils::DeserializeOptional<FString>("start_date", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("gift", Bag, Gift, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("end_date", Bag, EndDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>("stat_requirements", Bag, StatRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>("attachments", Bag, Attachments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("clientData", Bag, ClientData, OuterOwner);
}



