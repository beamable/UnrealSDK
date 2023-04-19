
#include "BeamableCore/Public/AutoGen/WebhookReward.h"
#include "Serialization/BeamJsonUtils.h"




void UWebhookReward::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UWebhookInvocationStrategy*>("strategy", Strategy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("webhookSymbol"), &WebhookSymbol, Serializer);
	UBeamJsonUtils::SerializeOptional<UWebhookComet*>(TEXT("webHookComet"), &WebHookComet, Serializer);
}

void UWebhookReward::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UWebhookInvocationStrategy*>("strategy", Strategy, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("webhookSymbol"), &WebhookSymbol, Serializer);
	UBeamJsonUtils::SerializeOptional<UWebhookComet*>(TEXT("webHookComet"), &WebHookComet, Serializer);		
}

void UWebhookReward::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UWebhookInvocationStrategy*>("strategy", Bag, Strategy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("webhookSymbol", Bag, WebhookSymbol, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UWebhookComet*>("webHookComet", Bag, WebHookComet, OuterOwner);
}



