
#include "BeamableCore/Public/AutoGen/MatchMakingWindowResp.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMatchMakingWindowResp::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("difficulty"), Difficulty, Serializer);
	UBeamJsonUtils::SerializeArray<UMatchMakingRanking*>(TEXT("matches"), Matches, Serializer);
}

void UMatchMakingWindowResp::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("difficulty"), Difficulty, Serializer);
	UBeamJsonUtils::SerializeArray<UMatchMakingRanking*>(TEXT("matches"), Matches, Serializer);		
}

void UMatchMakingWindowResp::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("difficulty"), Bag, Difficulty);
	UBeamJsonUtils::DeserializeArray<UMatchMakingRanking*>(TEXT("matches"), Bag, Matches, OuterOwner);
}



