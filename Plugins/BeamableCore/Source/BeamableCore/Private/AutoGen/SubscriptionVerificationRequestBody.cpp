
#include "BeamableCore/Public/AutoGen/SubscriptionVerificationRequestBody.h"





void USubscriptionVerificationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hubMode"), HubMode, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hubChallenge"), HubChallenge, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hubVerifyToken"), HubVerifyToken, Serializer);
}

void USubscriptionVerificationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hubMode"), HubMode, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hubChallenge"), HubChallenge, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hubVerifyToken"), HubVerifyToken, Serializer);		
}

void USubscriptionVerificationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hubMode")), HubMode);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hubChallenge")), HubChallenge);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hubVerifyToken")), HubVerifyToken);
}



