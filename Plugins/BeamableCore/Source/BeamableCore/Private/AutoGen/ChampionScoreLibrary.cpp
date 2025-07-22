
#include "BeamableCore/Public/AutoGen/ChampionScoreLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UChampionScoreLibrary::ChampionScoreToJsonString(const UChampionScore* Serializable, const bool Pretty)
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

UChampionScore* UChampionScoreLibrary::Make(int64 EndTimeMs, int64 StartTimeMs, double Score, int32 Cycle, int64 PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UChampionScore>(Outer);
	Serializable->EndTimeMs = EndTimeMs;
	Serializable->StartTimeMs = StartTimeMs;
	Serializable->Score = Score;
	Serializable->Cycle = Cycle;
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UChampionScoreLibrary::Break(const UChampionScore* Serializable, int64& EndTimeMs, int64& StartTimeMs, double& Score, int32& Cycle, int64& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		EndTimeMs = Serializable->EndTimeMs;
		StartTimeMs = Serializable->StartTimeMs;
		Score = Serializable->Score;
		Cycle = Serializable->Cycle;
		PlayerId = Serializable->PlayerId;
	}
		
}

