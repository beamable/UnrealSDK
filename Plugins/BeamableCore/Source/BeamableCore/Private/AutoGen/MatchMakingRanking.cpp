
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
	bIsUnranked = Bag->GetBoolField(TEXT("isUnranked"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gt")), Gt);
	Rank = Bag->GetIntegerField(TEXT("rank"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("variables")), Variables, OuterOwner);
}



