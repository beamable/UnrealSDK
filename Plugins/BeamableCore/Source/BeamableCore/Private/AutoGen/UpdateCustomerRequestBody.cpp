
#include "BeamableCore/Public/AutoGen/UpdateCustomerRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdateCustomerRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamPaymentStatus>(TEXT("paymentStatus"), &PaymentStatus, Serializer);
}

void UUpdateCustomerRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamPaymentStatus>(TEXT("paymentStatus"), &PaymentStatus, Serializer);		
}

void UUpdateCustomerRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<EBeamPaymentStatus>("paymentStatus", Bag, PaymentStatus, OuterOwner);
}



