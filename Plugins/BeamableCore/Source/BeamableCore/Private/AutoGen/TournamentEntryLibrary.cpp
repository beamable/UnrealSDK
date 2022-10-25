
#include "AutoGen/TournamentEntryLibrary.h"

#include "CoreMinimal.h"


FString UTournamentEntryLibrary::TournamentEntryToJsonString(const UTournamentEntry* Serializable, const bool Pretty)
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

UTournamentEntry* UTournamentEntryLibrary::Make(int64 Rank, double Score, int64 PlayerId, int32 StageChange, TArray<UTournamentCurrencyReward*> CurrencyRewards, UObject* Outer)
{
	auto Serializable = NewObject<UTournamentEntry>(Outer);
	Serializable->Rank = Rank;
	Serializable->Score = Score;
	Serializable->PlayerId = PlayerId;
	Serializable->StageChange = StageChange;
	Serializable->CurrencyRewards = CurrencyRewards;
	
	return Serializable;
}

void UTournamentEntryLibrary::Break(const UTournamentEntry* Serializable, int64& Rank, double& Score, int64& PlayerId, int32& StageChange, TArray<UTournamentCurrencyReward*>& CurrencyRewards)
{
	Rank = Serializable->Rank;
	Score = Serializable->Score;
	PlayerId = Serializable->PlayerId;
	StageChange = Serializable->StageChange;
	CurrencyRewards = Serializable->CurrencyRewards;
		
}

