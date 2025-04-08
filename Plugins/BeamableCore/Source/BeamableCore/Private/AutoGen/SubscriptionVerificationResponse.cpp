
#include "BeamableCore/Public/AutoGen/SubscriptionVerificationResponse.h"





void USubscriptionVerificationResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("hubChallenge"), HubChallenge);
}

void USubscriptionVerificationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("hubChallenge"), HubChallenge);		
}

void USubscriptionVerificationResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hubChallenge")), HubChallenge);
}



