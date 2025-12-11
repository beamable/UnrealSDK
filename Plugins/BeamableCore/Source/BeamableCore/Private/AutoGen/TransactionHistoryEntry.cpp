
#include "BeamableCore/Public/AutoGen/TransactionHistoryEntry.h"
#include "Serialization/BeamJsonUtils.h"




void UTransactionHistoryEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("change"), UBeamJsonUtils::EnumToSerializationName(Change));
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timestamp"), Timestamp, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("data"), &Data, Serializer);
}

void UTransactionHistoryEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("change"), UBeamJsonUtils::EnumToSerializationName(Change));
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timestamp"), Timestamp, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("data"), &Data, Serializer);		
}

void UTransactionHistoryEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("change"), Bag, Change);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("timestamp"), Bag, Timestamp);
	UBeamJsonUtils::DeserializeOptional<FString>("data", Bag, Data, OuterOwner);
}



