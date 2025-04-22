
#include "BeamableCore/Public/AutoGen/SubscriptionVerificationResponse.h"





void USubscriptionVerificationResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hubChallenge"), HubChallenge, Serializer);
}

void USubscriptionVerificationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hubChallenge"), HubChallenge, Serializer);		
}

void USubscriptionVerificationResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hubChallenge")), HubChallenge);
}



