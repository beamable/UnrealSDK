
#include "BeamableCore/Public/AutoGen/MatchMakingWindowResp.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMatchMakingWindowResp::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("difficulty"), Difficulty);
	UBeamJsonUtils::SerializeArray<UMatchMakingRanking*>(TEXT("matches"), Matches, Serializer);
}

void UMatchMakingWindowResp::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("difficulty"), Difficulty);
	UBeamJsonUtils::SerializeArray<UMatchMakingRanking*>(TEXT("matches"), Matches, Serializer);		
}

void UMatchMakingWindowResp::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("difficulty")), Difficulty);
	UBeamJsonUtils::DeserializeArray<UMatchMakingRanking*>(Bag->GetArrayField(TEXT("matches")), Matches, OuterOwner);
}



