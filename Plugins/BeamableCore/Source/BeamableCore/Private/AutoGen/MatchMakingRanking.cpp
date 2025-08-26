
#include "BeamableCore/Public/AutoGen/MatchMakingRanking.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMatchMakingRanking::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isUnranked"), bIsUnranked, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gt"), Gt, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("variables"), Variables, Serializer);
}

void UMatchMakingRanking::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isUnranked"), bIsUnranked, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gt"), Gt, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("variables"), Variables, Serializer);		
}

void UMatchMakingRanking::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isUnranked"), Bag, bIsUnranked);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gt"), Bag, Gt);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rank"), Bag, Rank);
	UBeamJsonUtils::DeserializeMap<FString>(TEXT("variables"), Bag, Variables, OuterOwner);
}



