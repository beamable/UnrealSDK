
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PerPlayerMatchResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPerPlayerMatchResultLibrary::PerPlayerMatchResultToJsonString(const UPerPlayerMatchResult* Serializable, const bool Pretty)
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

UPerPlayerMatchResult* UPerPlayerMatchResultLibrary::Make(bool bWon, int32 RankEarned, int32 CoinsEarned, UObject* Outer)
{
	auto Serializable = NewObject<UPerPlayerMatchResult>(Outer);
	Serializable->bWon = bWon;
	Serializable->RankEarned = RankEarned;
	Serializable->CoinsEarned = CoinsEarned;
	
	return Serializable;
}

void UPerPlayerMatchResultLibrary::Break(const UPerPlayerMatchResult* Serializable, bool& bWon, int32& RankEarned, int32& CoinsEarned)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bWon = Serializable->bWon;
		RankEarned = Serializable->RankEarned;
		CoinsEarned = Serializable->CoinsEarned;
	}
		
}

