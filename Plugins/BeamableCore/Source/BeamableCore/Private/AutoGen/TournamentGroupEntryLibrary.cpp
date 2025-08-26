
#include "BeamableCore/Public/AutoGen/TournamentGroupEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTournamentGroupEntryLibrary::TournamentGroupEntryToJsonString(const UTournamentGroupEntry* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UTournamentGroupEntry* UTournamentGroupEntryLibrary::Make(int64 Rank, double Score, int64 GroupId, int32 StageChange, TArray<UTournamentCurrencyReward*> CurrencyRewards, UObject* Outer)
{
	auto Serializable = NewObject<UTournamentGroupEntry>(Outer);
	Serializable->Rank = Rank;
	Serializable->Score = Score;
	Serializable->GroupId = GroupId;
	Serializable->StageChange = StageChange;
	Serializable->CurrencyRewards = CurrencyRewards;
	
	return Serializable;
}

void UTournamentGroupEntryLibrary::Break(const UTournamentGroupEntry* Serializable, int64& Rank, double& Score, int64& GroupId, int32& StageChange, TArray<UTournamentCurrencyReward*>& CurrencyRewards)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Rank = Serializable->Rank;
		Score = Serializable->Score;
		GroupId = Serializable->GroupId;
		StageChange = Serializable->StageChange;
		CurrencyRewards = Serializable->CurrencyRewards;
	}
		
}

