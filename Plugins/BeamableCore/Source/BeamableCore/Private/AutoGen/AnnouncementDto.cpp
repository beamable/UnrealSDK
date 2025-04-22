
#include "BeamableCore/Public/AutoGen/AnnouncementDto.h"
#include "Serialization/BeamJsonUtils.h"




void UAnnouncementDto::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("body", Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("channel"), Channel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("title", Title, Serializer);
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("summary", Summary, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start_date"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end_date"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>(TEXT("stat_requirements"), &StatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>(TEXT("attachments"), &Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("clientData"), &ClientData, Serializer);
}

void UAnnouncementDto::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("body", Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("channel"), Channel, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("title", Title, Serializer);
	UBeamJsonUtils::SerializeUObject<ULocalizationRef*>("summary", Summary, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("start_date"), &StartDate, Serializer);
	UBeamJsonUtils::SerializeOptional<UPlayerReward*>(TEXT("gift"), &Gift, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end_date"), &EndDate, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>(TEXT("stat_requirements"), &StatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>(TEXT("attachments"), &Attachments, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("clientData"), &ClientData, Serializer);		
}

void UAnnouncementDto::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<ULocalizationRef*>("body", Bag, Body, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("channel")), Channel);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeUObject<ULocalizationRef*>("title", Bag, Title, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<ULocalizationRef*>("summary", Bag, Summary, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("start_date", Bag, StartDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UPlayerReward*>("gift", Bag, Gift, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("end_date", Bag, EndDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UPlayerStatRequirement*>, UPlayerStatRequirement*>("stat_requirements", Bag, StatRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UAnnouncementAttachment*>, UAnnouncementAttachment*>("attachments", Bag, Attachments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("clientData", Bag, ClientData, OuterOwner);
}



