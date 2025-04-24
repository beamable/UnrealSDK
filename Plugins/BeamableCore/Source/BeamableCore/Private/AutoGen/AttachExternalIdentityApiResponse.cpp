
#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAttachExternalIdentityApiResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAttachExternalIdentityApiResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challenge_token"), &ChallengeToken, Serializer);
}

void UAttachExternalIdentityApiResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challenge_token"), &ChallengeToken, Serializer);		
}

void UAttachExternalIdentityApiResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("result")), Result);
	UBeamJsonUtils::DeserializeOptional<FString>("challenge_token", Bag, ChallengeToken, OuterOwner);
}



