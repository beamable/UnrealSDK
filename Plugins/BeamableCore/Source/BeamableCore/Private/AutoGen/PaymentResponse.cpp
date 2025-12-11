
#include "BeamableCore/Public/AutoGen/PaymentResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UPaymentResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPaymentResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("transactionId"), &TransactionId, Serializer);
}

void UPaymentResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("transactionId"), &TransactionId, Serializer);		
}

void UPaymentResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("transactionId", Bag, TransactionId, OuterOwner);
}



