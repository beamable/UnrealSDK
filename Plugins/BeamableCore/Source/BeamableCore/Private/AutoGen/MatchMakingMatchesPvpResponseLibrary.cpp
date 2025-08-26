
#include "BeamableCore/Public/AutoGen/MatchMakingMatchesPvpResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMatchMakingMatchesPvpResponseLibrary::MatchMakingMatchesPvpResponseToJsonString(const UMatchMakingMatchesPvpResponse* Serializable, const bool Pretty)
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

UMatchMakingMatchesPvpResponse* UMatchMakingMatchesPvpResponseLibrary::Make(FString Result, int32 TotalEntries, UMatchMakingRanking* PlayerRank, TArray<UMatchMakingWindowResp*> Windows, UObject* Outer)
{
	auto Serializable = NewObject<UMatchMakingMatchesPvpResponse>(Outer);
	Serializable->Result = Result;
	Serializable->TotalEntries = TotalEntries;
	Serializable->PlayerRank = PlayerRank;
	Serializable->Windows = Windows;
	
	return Serializable;
}

void UMatchMakingMatchesPvpResponseLibrary::Break(const UMatchMakingMatchesPvpResponse* Serializable, FString& Result, int32& TotalEntries, UMatchMakingRanking*& PlayerRank, TArray<UMatchMakingWindowResp*>& Windows)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
		TotalEntries = Serializable->TotalEntries;
		PlayerRank = Serializable->PlayerRank;
		Windows = Serializable->Windows;
	}
		
}

