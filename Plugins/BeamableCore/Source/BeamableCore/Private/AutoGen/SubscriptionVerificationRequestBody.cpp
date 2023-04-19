
#include "BeamableCore/Public/AutoGen/SubscriptionVerificationRequestBody.h"





void USubscriptionVerificationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("hubMode"), HubMode);
	Serializer->WriteValue(TEXT("hubChallenge"), HubChallenge);
	Serializer->WriteValue(TEXT("hubVerifyToken"), HubVerifyToken);
}

void USubscriptionVerificationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("hubMode"), HubMode);
	Serializer->WriteValue(TEXT("hubChallenge"), HubChallenge);
	Serializer->WriteValue(TEXT("hubVerifyToken"), HubVerifyToken);		
}

void USubscriptionVerificationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	HubMode = Bag->GetStringField(TEXT("hubMode"));
	HubChallenge = Bag->GetStringField(TEXT("hubChallenge"));
	HubVerifyToken = Bag->GetStringField(TEXT("hubVerifyToken"));
}



