
#include "BeamableCore/Public/AutoGen/LeaderboardAddRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void ULeaderboardAddRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("maxScore"), &MaxScore, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("minScore"), &MinScore, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);
}

void ULeaderboardAddRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("maxScore"), &MaxScore, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("minScore"), &MinScore, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);		
}

void ULeaderboardAddRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Score = Bag->GetNumberField(TEXT("score"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeOptional<bool>("increment", Bag, bIncrement, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<double>("maxScore", Bag, MaxScore, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<double>("minScore", Bag, MinScore, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("stats", Bag, Stats, OuterOwner);
}



