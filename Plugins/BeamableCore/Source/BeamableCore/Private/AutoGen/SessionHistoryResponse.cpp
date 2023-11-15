
#include "BeamableCore/Public/AutoGen/SessionHistoryResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void USessionHistoryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USessionHistoryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<ULocalDate*>("date", Date, Serializer);
	Serializer->WriteValue(TEXT("daysPlayed"), DaysPlayed);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("payments"), Payments, Serializer);
	UBeamJsonUtils::SerializeArray<UPaymentTotal*>(TEXT("totalPaid"), TotalPaid, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("sessions"), Sessions, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("installDate"), &InstallDate, Serializer);
}

void USessionHistoryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<ULocalDate*>("date", Date, Serializer);
	Serializer->WriteValue(TEXT("daysPlayed"), DaysPlayed);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("payments"), Payments, Serializer);
	UBeamJsonUtils::SerializeArray<UPaymentTotal*>(TEXT("totalPaid"), TotalPaid, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("sessions"), Sessions, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("installDate"), &InstallDate, Serializer);		
}

void USessionHistoryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<ULocalDate*>("date", Bag, Date, OuterOwner);
	DaysPlayed = Bag->GetIntegerField(TEXT("daysPlayed"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("payments")), Payments, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPaymentTotal*>(Bag->GetArrayField(TEXT("totalPaid")), TotalPaid, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("sessions")), Sessions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("installDate", Bag, InstallDate, OuterOwner);
}



