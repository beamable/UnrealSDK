
#include "AutoGen/AnnouncementDto.h"
#include "Serialization/BeamJsonUtils.h"


void UAnnouncementDto ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("body", Body, Serializer);
	Serializer->WriteValue(TEXT("channel"), Channel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start_date"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>(TEXT("stat_requirements"), &StatRequirements, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end_date"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("title", Title, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>(TEXT("attachments"), &Attachments, Serializer);
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("summary", Summary, Serializer);
}

void UAnnouncementDto::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("body", Body, Serializer);
	Serializer->WriteValue(TEXT("channel"), Channel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start_date"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>(TEXT("stat_requirements"), &StatRequirements, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end_date"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("title", Title, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>(TEXT("attachments"), &Attachments, Serializer);
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("summary", Summary, Serializer);		
}

void UAnnouncementDto ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<ULocalizationRef*>("body", Bag, Body, OuterOwner);
	Channel = Bag->GetStringField(TEXT("channel"));
	UBeamJsonUtils::DeserializeOptional<FString>("start_date", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("gift", Bag, Gift, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>("stat_requirements", Bag, StatRequirements, OuterOwner);
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("clientData", Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("end_date", Bag, EndDate, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<ULocalizationRef*>("title", Bag, Title, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>("attachments", Bag, Attachments, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<ULocalizationRef*>("summary", Bag, Summary, OuterOwner);
}