
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
	HubChallenge = Bag->GetStringField(TEXT("hubChallenge"));
}



