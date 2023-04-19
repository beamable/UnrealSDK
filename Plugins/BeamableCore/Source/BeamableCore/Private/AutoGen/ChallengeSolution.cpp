
#include "BeamableCore/Public/AutoGen/ChallengeSolution.h"





void UChallengeSolution::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("challenge_token"), ChallengeToken);
	Serializer->WriteValue(TEXT("solution"), Solution);
}

void UChallengeSolution::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("challenge_token"), ChallengeToken);
	Serializer->WriteValue(TEXT("solution"), Solution);		
}

void UChallengeSolution::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ChallengeToken = Bag->GetStringField(TEXT("challenge_token"));
	Solution = Bag->GetStringField(TEXT("solution"));
}



