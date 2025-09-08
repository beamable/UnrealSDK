
#include "BeamableCore/Public/AutoGen/SignupVerificationResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USignupVerificationResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USignupVerificationResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UAccountPlayerView*>("account", Account, Serializer);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);
}

void USignupVerificationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UAccountPlayerView*>("account", Account, Serializer);
	UBeamJsonUtils::SerializeUObject<UTokenResponse*>("token", Token, Serializer);		
}

void USignupVerificationResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UAccountPlayerView*>("account", Bag, Account, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UTokenResponse*>("token", Bag, Token, OuterOwner);
}



