
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("challenge_token"), Bag, ChallengeToken);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("solution"), Bag, Solution);
}



