
#include "BeamableCore/Public/AutoGen/InventoryUpdateDeltaLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInventoryUpdateDeltaLibrary::InventoryUpdateDeltaToJsonString(const UInventoryUpdateDelta* Serializable, const bool Pretty)
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

UInventoryUpdateDelta* UInventoryUpdateDeltaLibrary::Make(UItemDeltas* Items, TMap<FString, UCurrencyDelta*> Currencies, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryUpdateDelta>(Outer);
	Serializable->Items = Items;
	Serializable->Currencies = Currencies;
	
	return Serializable;
}

void UInventoryUpdateDeltaLibrary::Break(const UInventoryUpdateDelta* Serializable, UItemDeltas*& Items, TMap<FString, UCurrencyDelta*>& Currencies)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Items = Serializable->Items;
		Currencies = Serializable->Currencies;
	}
		
}

