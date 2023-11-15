
#include "BeamableCore/Public/AutoGen/SessionClientHistoryResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void USessionClientHistoryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USessionClientHistoryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<ULocalDate*>("date", Date, Serializer);
	Serializer->WriteValue(TEXT("daysPlayed"), DaysPlayed);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("sessions"), Sessions, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("installDate"), &InstallDate, Serializer);
}

void USessionClientHistoryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<ULocalDate*>("date", Date, Serializer);
	Serializer->WriteValue(TEXT("daysPlayed"), DaysPlayed);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("sessions"), Sessions, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("installDate"), &InstallDate, Serializer);		
}

void USessionClientHistoryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<ULocalDate*>("date", Bag, Date, OuterOwner);
	DaysPlayed = Bag->GetIntegerField(TEXT("daysPlayed"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("sessions")), Sessions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("installDate", Bag, InstallDate, OuterOwner);
}



