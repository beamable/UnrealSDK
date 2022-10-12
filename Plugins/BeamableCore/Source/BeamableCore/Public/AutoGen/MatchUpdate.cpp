
#include "AutoGen/MatchUpdate.h"
#include "Serialization/BeamJsonUtils.h"


void UMatchUpdate ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int64>(TEXT("players"), Players, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemaining"), &SecondsRemaining, Serializer);
	Serializer->WriteValue(TEXT("minPlayersReached"), bMinPlayersReached);
	Serializer->WriteValue(TEXT("gameStarted"), bGameStarted);
	Serializer->WriteValue(TEXT("game"), Game);
}

void UMatchUpdate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int64>(TEXT("players"), Players, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemaining"), &SecondsRemaining, Serializer);
	Serializer->WriteValue(TEXT("minPlayersReached"), bMinPlayersReached);
	Serializer->WriteValue(TEXT("gameStarted"), bGameStarted);
	Serializer->WriteValue(TEXT("game"), Game);		
}

void UMatchUpdate ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("players")), Players, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemaining", Bag, SecondsRemaining, OuterOwner);
	bMinPlayersReached = Bag->GetBoolField(TEXT("minPlayersReached"));
	bGameStarted = Bag->GetBoolField(TEXT("gameStarted"));
	Game = Bag->GetStringField(TEXT("game"));
}