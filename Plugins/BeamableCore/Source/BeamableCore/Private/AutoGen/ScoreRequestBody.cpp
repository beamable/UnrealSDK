
#include "BeamableCore/Public/AutoGen/ScoreRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UScoreRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);
}

void UScoreRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);		
}

void UScoreRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	Score = Bag->GetNumberField(TEXT("score"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	UBeamJsonUtils::DeserializeOptional<bool>("increment", Bag, bIncrement, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("stats", Bag, Stats, OuterOwner);
}



