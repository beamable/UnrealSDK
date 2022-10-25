
#include "AutoGen/MatchUpdate.h"
#include "Serialization/BeamJsonUtils.h"


void UMatchUpdate ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("game"), Game);
	Serializer->WriteValue(TEXT("gameStarted"), bGameStarted);
	Serializer->WriteValue(TEXT("minPlayersReached"), bMinPlayersReached);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("players"), Players, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemaining"), &SecondsRemaining, Serializer);
}

void UMatchUpdate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("game"), Game);
	Serializer->WriteValue(TEXT("gameStarted"), bGameStarted);
	Serializer->WriteValue(TEXT("minPlayersReached"), bMinPlayersReached);
	UBeamJsonUtils::SerializeArray<int64>(TEXT("players"), Players, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemaining"), &SecondsRemaining, Serializer);		
}

void UMatchUpdate ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Game = Bag->GetStringField(TEXT("game"));
	bGameStarted = Bag->GetBoolField(TEXT("gameStarted"));
	bMinPlayersReached = Bag->GetBoolField(TEXT("minPlayersReached"));
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("players")), Players, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemaining", Bag, SecondsRemaining, OuterOwner);
}