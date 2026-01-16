
#include "BeamableCore/Public/AutoGen/BeginPaymentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBeginPaymentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("paymentProvider"), PaymentProvider, Serializer);
	UBeamJsonUtils::SerializeUObject<UTransactionDetails*>("details", Details, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("initHistoryData"), &InitHistoryData, Serializer);
}

void UBeginPaymentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("paymentProvider"), PaymentProvider, Serializer);
	UBeamJsonUtils::SerializeUObject<UTransactionDetails*>("details", Details, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("initHistoryData"), &InitHistoryData, Serializer);		
}

void UBeginPaymentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("paymentProvider"), Bag, PaymentProvider);
	UBeamJsonUtils::DeserializeUObject<UTransactionDetails*>("details", Bag, Details, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("initHistoryData", Bag, InitHistoryData, OuterOwner);
}



