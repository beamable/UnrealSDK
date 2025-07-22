
#include "BeamableCore/Public/AutoGen/LocalizedPriceMapLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULocalizedPriceMapLibrary::LocalizedPriceMapToJsonString(const ULocalizedPriceMap* Serializable, const bool Pretty)
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

ULocalizedPriceMap* ULocalizedPriceMapLibrary::Make(FString Currency, TArray<ULocalizedPrice*> Prices, UObject* Outer)
{
	auto Serializable = NewObject<ULocalizedPriceMap>(Outer);
	Serializable->Currency = Currency;
	Serializable->Prices = Prices;
	
	return Serializable;
}

void ULocalizedPriceMapLibrary::Break(const ULocalizedPriceMap* Serializable, FString& Currency, TArray<ULocalizedPrice*>& Prices)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Currency = Serializable->Currency;
		Prices = Serializable->Prices;
	}
		
}

