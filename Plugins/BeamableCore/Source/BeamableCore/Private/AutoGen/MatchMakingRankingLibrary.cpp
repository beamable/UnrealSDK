
#include "BeamableCore/Public/AutoGen/MatchMakingRankingLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMatchMakingRankingLibrary::MatchMakingRankingToJsonString(const UMatchMakingRanking* Serializable, const bool Pretty)
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

UMatchMakingRanking* UMatchMakingRankingLibrary::Make(bool bIsUnranked, int64 Gt, int32 Rank, TMap<FString, FString> Variables, UObject* Outer)
{
	auto Serializable = NewObject<UMatchMakingRanking>(Outer);
	Serializable->bIsUnranked = bIsUnranked;
	Serializable->Gt = Gt;
	Serializable->Rank = Rank;
	Serializable->Variables = Variables;
	
	return Serializable;
}

void UMatchMakingRankingLibrary::Break(const UMatchMakingRanking* Serializable, bool& bIsUnranked, int64& Gt, int32& Rank, TMap<FString, FString>& Variables)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsUnranked = Serializable->bIsUnranked;
		Gt = Serializable->Gt;
		Rank = Serializable->Rank;
		Variables = Serializable->Variables;
	}
		
}

