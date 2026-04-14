
#include "BeamableCore/Public/AutoGen/SessionClientHistoryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USessionClientHistoryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USessionClientHistoryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("date"), &Date, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("installDate"), &InstallDate, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("daysPlayed"), &DaysPlayed, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("sessions"), &Sessions, Serializer);
}

void USessionClientHistoryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("date"), &Date, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("installDate"), &InstallDate, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("daysPlayed"), &DaysPlayed, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("sessions"), &Sessions, Serializer);		
}

void USessionClientHistoryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("date", Bag, Date, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("installDate", Bag, InstallDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("daysPlayed", Bag, DaysPlayed, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("sessions", Bag, Sessions, OuterOwner);
}



