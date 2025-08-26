
#include "BeamableCore/Public/AutoGen/RewardsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URewardsResponseLibrary::RewardsResponseToJsonString(const URewardsResponse* Serializable, const bool Pretty)
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

URewardsResponse* URewardsResponseLibrary::Make(TArray<UTournamentCurrencyReward*> RewardCurrencies, UObject* Outer)
{
	auto Serializable = NewObject<URewardsResponse>(Outer);
	Serializable->RewardCurrencies = RewardCurrencies;
	
	return Serializable;
}

void URewardsResponseLibrary::Break(const URewardsResponse* Serializable, TArray<UTournamentCurrencyReward*>& RewardCurrencies)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RewardCurrencies = Serializable->RewardCurrencies;
	}
		
}

