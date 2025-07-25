
#include "BeamableCore/Public/AutoGen/EventInventoryRewardCurrencyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventInventoryRewardCurrencyLibrary::EventInventoryRewardCurrencyToJsonString(const UEventInventoryRewardCurrency* Serializable, const bool Pretty)
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

UEventInventoryRewardCurrency* UEventInventoryRewardCurrencyLibrary::Make(FString Id, int64 Amount, UObject* Outer)
{
	auto Serializable = NewObject<UEventInventoryRewardCurrency>(Outer);
	Serializable->Id = Id;
	Serializable->Amount = Amount;
	
	return Serializable;
}

void UEventInventoryRewardCurrencyLibrary::Break(const UEventInventoryRewardCurrency* Serializable, FString& Id, int64& Amount)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Amount = Serializable->Amount;
	}
		
}

