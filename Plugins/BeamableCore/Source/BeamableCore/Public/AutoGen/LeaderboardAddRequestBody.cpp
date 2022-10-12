
#include "AutoGen/LeaderboardAddRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void ULeaderboardAddRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<double>(TEXT("maxScore"), &MaxScore, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("minScore"), &MinScore, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);
}

void ULeaderboardAddRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<double>(TEXT("maxScore"), &MaxScore, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("minScore"), &MinScore, Serializer);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);		
}

void ULeaderboardAddRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<double>("maxScore", Bag, MaxScore, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("stats", Bag, Stats, OuterOwner);
	Score = Bag->GetNumberField(TEXT("score"));
	UBeamJsonUtils::DeserializeOptional<double>("minScore", Bag, MinScore, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeOptional<bool>("increment", Bag, bIncrement, OuterOwner);
}