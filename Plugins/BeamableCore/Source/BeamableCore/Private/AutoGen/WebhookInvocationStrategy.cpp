
#include "BeamableCore/Public/AutoGen/WebhookInvocationStrategy.h"





void UWebhookInvocationStrategy::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("invocationType"), UWebhookInvocationTypeLibrary::WebhookInvocationTypeToSerializationName(InvocationType));
	Serializer->WriteValue(TEXT("retryType"), UWebhookRetryTypeLibrary::WebhookRetryTypeToSerializationName(RetryType));
}

void UWebhookInvocationStrategy::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("invocationType"), UWebhookInvocationTypeLibrary::WebhookInvocationTypeToSerializationName(InvocationType));
	Serializer->WriteValue(TEXT("retryType"), UWebhookRetryTypeLibrary::WebhookRetryTypeToSerializationName(RetryType));		
}

void UWebhookInvocationStrategy::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	InvocationType = UWebhookInvocationTypeLibrary::SerializationNameToWebhookInvocationType(Bag->GetStringField(TEXT("invocationType")));
	RetryType = UWebhookRetryTypeLibrary::SerializationNameToWebhookRetryType(Bag->GetStringField(TEXT("retryType")));
}



