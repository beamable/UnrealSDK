
#include "BeamableCore/Public/AutoGen/MatchMakingRanking.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMatchMakingRanking::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isUnranked"), bIsUnranked);
	Serializer->WriteValue(TEXT("gt"), Gt);
	Serializer->WriteValue(TEXT("rank"), Rank);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("variables"), Variables, Serializer);
}

void UMatchMakingRanking::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isUnranked"), bIsUnranked);
	Serializer->WriteValue(TEXT("gt"), Gt);
	Serializer->WriteValue(TEXT("rank"), Rank);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("variables"), Variables, Serializer);		
}

void UMatchMakingRanking::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isUnranked")), bIsUnranked);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gt")), Gt);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("rank")), Rank);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("variables")), Variables, OuterOwner);
}



