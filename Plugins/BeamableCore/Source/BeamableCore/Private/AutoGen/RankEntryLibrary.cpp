
#include "BeamableCore/Public/AutoGen/RankEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URankEntryLibrary::RankEntryToJsonString(const URankEntry* Serializable, const bool Pretty)
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

URankEntry* URankEntryLibrary::Make(int64 Rank, int64 Gt, TMap<FString, int64> Columns, FOptionalDouble Score, FOptionalArrayOfRankEntryStat Stats, UObject* Outer)
{
	auto Serializable = NewObject<URankEntry>(Outer);
	Serializable->Rank = Rank;
	Serializable->Gt = Gt;
	Serializable->Columns = Columns;
	Serializable->Score = Score;
	Serializable->Stats = Stats;
	
	return Serializable;
}

void URankEntryLibrary::Break(const URankEntry* Serializable, int64& Rank, int64& Gt, TMap<FString, int64>& Columns, FOptionalDouble& Score, FOptionalArrayOfRankEntryStat& Stats)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Rank = Serializable->Rank;
		Gt = Serializable->Gt;
		Columns = Serializable->Columns;
		Score = Serializable->Score;
		Stats = Serializable->Stats;
	}
		
}

