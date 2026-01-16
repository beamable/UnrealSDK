
#include "BeamableCore/Public/AutoGen/CompletePaymentRequestBody.h"





void UCompletePaymentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("paymentProvider"), PaymentProvider, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("receipt"), Receipt, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
}

void UCompletePaymentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("paymentProvider"), PaymentProvider, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("receipt"), Receipt, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);		
}

void UCompletePaymentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("paymentProvider"), Bag, PaymentProvider);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("receipt"), Bag, Receipt);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
}



