
#include "BeamableCore/Public/AutoGen/MailRewardsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMailRewardsLibrary::MailRewardsToJsonString(const UMailRewards* Serializable, const bool Pretty)
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

UMailRewards* UMailRewardsLibrary::Make(TArray<UCurrencyChange*> Currencies, TArray<UItemCreateRequestBody*> Items, FOptionalBool bApplyVipBonus, UObject* Outer)
{
	auto Serializable = NewObject<UMailRewards>(Outer);
	Serializable->Currencies = Currencies;
	Serializable->Items = Items;
	Serializable->bApplyVipBonus = bApplyVipBonus;
	
	return Serializable;
}

void UMailRewardsLibrary::Break(const UMailRewards* Serializable, TArray<UCurrencyChange*>& Currencies, TArray<UItemCreateRequestBody*>& Items, FOptionalBool& bApplyVipBonus)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Currencies = Serializable->Currencies;
		Items = Serializable->Items;
		bApplyVipBonus = Serializable->bApplyVipBonus;
	}
		
}

