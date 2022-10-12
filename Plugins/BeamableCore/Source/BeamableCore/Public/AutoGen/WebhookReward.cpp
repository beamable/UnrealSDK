
#include "AutoGen/WebhookReward.h"
#include "Serialization/BeamJsonUtils.h"


void UWebhookReward ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("webhookSymbol"), &WebhookSymbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UWebhookInvocationStrategy*>("strategy", Strategy, Serializer);
	UBeamJsonUtils::SerializeOptional<UWebhookComet*>(TEXT("webHookComet"), &WebHookComet, Serializer);
}

void UWebhookReward::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("webhookSymbol"), &WebhookSymbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UWebhookInvocationStrategy*>("strategy", Strategy, Serializer);
	UBeamJsonUtils::SerializeOptional<UWebhookComet*>(TEXT("webHookComet"), &WebHookComet, Serializer);		
}

void UWebhookReward ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("webhookSymbol", Bag, WebhookSymbol, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UWebhookInvocationStrategy*>("strategy", Bag, Strategy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UWebhookComet*>("webHookComet", Bag, WebHookComet, OuterOwner);
}