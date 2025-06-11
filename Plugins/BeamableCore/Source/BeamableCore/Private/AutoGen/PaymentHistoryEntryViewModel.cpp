
#include "BeamableCore/Public/AutoGen/PaymentHistoryEntryViewModel.h"
#include "Serialization/BeamJsonUtils.h"




void UPaymentHistoryEntryViewModel::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("change"), Change, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("data"), &Data, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("timestamp"), &Timestamp, Serializer);
}

void UPaymentHistoryEntryViewModel::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("change"), Change, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("data"), &Data, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("timestamp"), &Timestamp, Serializer);		
}

void UPaymentHistoryEntryViewModel::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("change")), Change);
	UBeamJsonUtils::DeserializeOptional<FString>("data", Bag, Data, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("timestamp", Bag, Timestamp, OuterOwner);
}



