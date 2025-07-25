
#include "BeamableCore/Public/AutoGen/TournamentCurrencyRewardLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTournamentCurrencyRewardLibrary::TournamentCurrencyRewardToJsonString(const UTournamentCurrencyReward* Serializable, const bool Pretty)
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

UTournamentCurrencyReward* UTournamentCurrencyRewardLibrary::Make(FString Symbol, int64 Amount, UObject* Outer)
{
	auto Serializable = NewObject<UTournamentCurrencyReward>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Amount = Amount;
	
	return Serializable;
}

void UTournamentCurrencyRewardLibrary::Break(const UTournamentCurrencyReward* Serializable, FString& Symbol, int64& Amount)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Amount = Serializable->Amount;
	}
		
}

