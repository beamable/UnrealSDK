
#include "BeamableCore/Public/AutoGen/MatchUpdateLibrary.h"

#include "CoreMinimal.h"


FString UMatchUpdateLibrary::MatchUpdateToJsonString(const UMatchUpdate* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UMatchUpdate* UMatchUpdateLibrary::Make(FString Game, bool bGameStarted, bool bMinPlayersReached, TArray<int64> Players, FOptionalInt64 SecondsRemaining, UObject* Outer)
{
	auto Serializable = NewObject<UMatchUpdate>(Outer);
	Serializable->Game = Game;
	Serializable->bGameStarted = bGameStarted;
	Serializable->bMinPlayersReached = bMinPlayersReached;
	Serializable->Players = Players;
	Serializable->SecondsRemaining = SecondsRemaining;
	
	return Serializable;
}

void UMatchUpdateLibrary::Break(const UMatchUpdate* Serializable, FString& Game, bool& bGameStarted, bool& bMinPlayersReached, TArray<int64>& Players, FOptionalInt64& SecondsRemaining)
{
	Game = Serializable->Game;
	bGameStarted = Serializable->bGameStarted;
	bMinPlayersReached = Serializable->bMinPlayersReached;
	Players = Serializable->Players;
	SecondsRemaining = Serializable->SecondsRemaining;
		
}

