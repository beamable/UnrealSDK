
#include "AutoGen/MatchMakingRanking.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UMatchMakingRanking ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("gt"), Gt);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("isUnranked"), bIsUnranked);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("variables"), Variables, Serializer);
}

void UMatchMakingRanking::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("gt"), Gt);
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("isUnranked"), bIsUnranked);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("variables"), Variables, Serializer);		
}

void UMatchMakingRanking ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gt")), Gt);
	Rank = Bag->GetIntegerField(TEXT("rank"));
	bIsUnranked = Bag->GetBoolField(TEXT("isUnranked"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("variables")), Variables, OuterOwner);
}