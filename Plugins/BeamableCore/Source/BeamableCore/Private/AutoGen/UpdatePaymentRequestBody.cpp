
#include "BeamableCore/Public/AutoGen/UpdatePaymentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdatePaymentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("state"), UBeamJsonUtils::EnumToSerializationName(State));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("reason"), &Reason, Serializer);
}

void UUpdatePaymentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("state"), UBeamJsonUtils::EnumToSerializationName(State));
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("reason"), &Reason, Serializer);		
}

void UUpdatePaymentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("state"), Bag, State);
	UBeamJsonUtils::DeserializeOptional<FString>("reason", Bag, Reason, OuterOwner);
}



