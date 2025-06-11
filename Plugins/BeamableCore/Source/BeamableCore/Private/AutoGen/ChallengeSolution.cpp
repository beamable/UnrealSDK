
#include "BeamableCore/Public/AutoGen/ChallengeSolution.h"





void UChallengeSolution::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("challenge_token"), ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("solution"), Solution, Serializer);
}

void UChallengeSolution::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("challenge_token"), ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("solution"), Solution, Serializer);		
}

void UChallengeSolution::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("challenge_token")), ChallengeToken);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("solution")), Solution);
}



