
#include "AutoGen/SubscriptionVerificationResponse.h"



void USubscriptionVerificationResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("hubChallenge"), HubChallenge);
	Serializer->WriteValue(TEXT("contentType"), ContentType);
}

void USubscriptionVerificationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("hubChallenge"), HubChallenge);
	Serializer->WriteValue(TEXT("contentType"), ContentType);		
}

void USubscriptionVerificationResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	HubChallenge = Bag->GetStringField(TEXT("hubChallenge"));
	ContentType = Bag->GetStringField(TEXT("contentType"));
}