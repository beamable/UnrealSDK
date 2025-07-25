
#include "BeamableCore/Public/AutoGen/TournamentEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTournamentEntryLibrary::TournamentEntryToJsonString(const UTournamentEntry* Serializable, const bool Pretty)
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

UTournamentEntry* UTournamentEntryLibrary::Make(int32 Stage, int32 Tier, int64 Rank, double Score, int64 PlayerId, int32 StageChange, TArray<UTournamentCurrencyReward*> CurrencyRewards, FOptionalInt32 PreviousStageChange, FOptionalInt32 NextStageChange, UObject* Outer)
{
	auto Serializable = NewObject<UTournamentEntry>(Outer);
	Serializable->Stage = Stage;
	Serializable->Tier = Tier;
	Serializable->Rank = Rank;
	Serializable->Score = Score;
	Serializable->PlayerId = PlayerId;
	Serializable->StageChange = StageChange;
	Serializable->CurrencyRewards = CurrencyRewards;
	Serializable->PreviousStageChange = PreviousStageChange;
	Serializable->NextStageChange = NextStageChange;
	
	return Serializable;
}

void UTournamentEntryLibrary::Break(const UTournamentEntry* Serializable, int32& Stage, int32& Tier, int64& Rank, double& Score, int64& PlayerId, int32& StageChange, TArray<UTournamentCurrencyReward*>& CurrencyRewards, FOptionalInt32& PreviousStageChange, FOptionalInt32& NextStageChange)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Stage = Serializable->Stage;
		Tier = Serializable->Tier;
		Rank = Serializable->Rank;
		Score = Serializable->Score;
		PlayerId = Serializable->PlayerId;
		StageChange = Serializable->StageChange;
		CurrencyRewards = Serializable->CurrencyRewards;
		PreviousStageChange = Serializable->PreviousStageChange;
		NextStageChange = Serializable->NextStageChange;
	}
		
}

