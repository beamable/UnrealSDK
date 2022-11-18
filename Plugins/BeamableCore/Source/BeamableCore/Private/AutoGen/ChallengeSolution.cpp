
#include "AutoGen/ChallengeSolution.h"





void UChallengeSolution ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("challengeToken"), ChallengeToken);
	Serializer->WriteValue(TEXT("solution"), Solution);
}

void UChallengeSolution::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("challengeToken"), ChallengeToken);
	Serializer->WriteValue(TEXT("solution"), Solution);		
}

void UChallengeSolution ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ChallengeToken = Bag->GetStringField(TEXT("challengeToken"));
	Solution = Bag->GetStringField(TEXT("solution"));
}