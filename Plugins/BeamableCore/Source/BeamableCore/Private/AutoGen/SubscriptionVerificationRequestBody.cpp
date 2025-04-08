
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hubMode")), HubMode);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hubChallenge")), HubChallenge);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hubVerifyToken")), HubVerifyToken);
}



