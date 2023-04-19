
#include "BeamableCore/Public/AutoGen/PaymentHistoryEntryViewModel.h"
#include "Serialization/BeamJsonUtils.h"




void UPaymentHistoryEntryViewModel::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("change"), Change);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("data"), &Data, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("timestamp"), &Timestamp, Serializer);
}

void UPaymentHistoryEntryViewModel::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("change"), Change);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("data"), &Data, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("timestamp"), &Timestamp, Serializer);		
}

void UPaymentHistoryEntryViewModel::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Change = Bag->GetStringField(TEXT("change"));
	UBeamJsonUtils::DeserializeOptional<FString>("data", Bag, Data, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("timestamp", Bag, Timestamp, OuterOwner);
}



