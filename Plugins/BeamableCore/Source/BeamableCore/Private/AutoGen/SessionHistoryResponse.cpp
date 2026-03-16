
#include "BeamableCore/Public/AutoGen/SessionHistoryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USessionHistoryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USessionHistoryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("date"), &Date, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("installDate"), &InstallDate, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("daysPlayed"), &DaysPlayed, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("sessions"), &Sessions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("payments"), &Payments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerSessionActorPaymentTotal*>, UPlayerSessionActorPaymentTotal*>(TEXT("totalPaid"), &TotalPaid, Serializer);
}

void USessionHistoryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("date"), &Date, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("installDate"), &InstallDate, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("daysPlayed"), &DaysPlayed, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("sessions"), &Sessions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("payments"), &Payments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPlayerSessionActorPaymentTotal*>, UPlayerSessionActorPaymentTotal*>(TEXT("totalPaid"), &TotalPaid, Serializer);		
}

void USessionHistoryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("date", Bag, Date, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("installDate", Bag, InstallDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("daysPlayed", Bag, DaysPlayed, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("sessions", Bag, Sessions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("payments", Bag, Payments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UPlayerSessionActorPaymentTotal*>, UPlayerSessionActorPaymentTotal*>("totalPaid", Bag, TotalPaid, OuterOwner);
}



