
#include "BeamableCore/Public/AutoGen/AuthV2ChallengeSolution.h"
#include "Serialization/BeamJsonUtils.h"




void UAuthV2ChallengeSolution::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challengeToken"), &ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("solution"), &Solution, Serializer);
}

void UAuthV2ChallengeSolution::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challengeToken"), &ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("solution"), &Solution, Serializer);		
}

void UAuthV2ChallengeSolution::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("challengeToken", Bag, ChallengeToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("solution", Bag, Solution, OuterOwner);
}



