
#include "BeamableCore/Public/AutoGen/CurrencyChangeRewardLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCurrencyChangeRewardLibrary::CurrencyChangeRewardToJsonString(const UCurrencyChangeReward* Serializable, const bool Pretty)
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

UCurrencyChangeReward* UCurrencyChangeRewardLibrary::Make(FString Symbol, int64 Amount, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyChangeReward>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Amount = Amount;
	
	return Serializable;
}

void UCurrencyChangeRewardLibrary::Break(const UCurrencyChangeReward* Serializable, FString& Symbol, int64& Amount)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Amount = Serializable->Amount;
	}
		
}

