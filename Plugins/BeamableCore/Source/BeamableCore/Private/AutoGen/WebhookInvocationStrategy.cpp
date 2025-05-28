
#include "BeamableCore/Public/AutoGen/WebhookInvocationStrategy.h"





void UWebhookInvocationStrategy::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("invocationType"), UBeamJsonUtils::EnumToSerializationName(InvocationType));
	Serializer->WriteValue(TEXT("retryType"), UBeamJsonUtils::EnumToSerializationName(RetryType));
}

void UWebhookInvocationStrategy::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("invocationType"), UBeamJsonUtils::EnumToSerializationName(InvocationType));
	Serializer->WriteValue(TEXT("retryType"), UBeamJsonUtils::EnumToSerializationName(RetryType));		
}

void UWebhookInvocationStrategy::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("invocationType")), InvocationType);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("retryType")), RetryType);
}



