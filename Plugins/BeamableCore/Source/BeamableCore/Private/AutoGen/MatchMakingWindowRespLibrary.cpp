
#include "BeamableCore/Public/AutoGen/MatchMakingWindowRespLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMatchMakingWindowRespLibrary::MatchMakingWindowRespToJsonString(const UMatchMakingWindowResp* Serializable, const bool Pretty)
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

UMatchMakingWindowResp* UMatchMakingWindowRespLibrary::Make(int32 Difficulty, TArray<UMatchMakingRanking*> Matches, UObject* Outer)
{
	auto Serializable = NewObject<UMatchMakingWindowResp>(Outer);
	Serializable->Difficulty = Difficulty;
	Serializable->Matches = Matches;
	
	return Serializable;
}

void UMatchMakingWindowRespLibrary::Break(const UMatchMakingWindowResp* Serializable, int32& Difficulty, TArray<UMatchMakingRanking*>& Matches)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Difficulty = Serializable->Difficulty;
		Matches = Serializable->Matches;
	}
		
}

