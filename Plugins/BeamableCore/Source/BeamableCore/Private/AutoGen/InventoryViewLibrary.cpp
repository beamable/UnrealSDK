
#include "BeamableCore/Public/AutoGen/InventoryViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInventoryViewLibrary::InventoryViewToJsonString(const UInventoryView* Serializable, const bool Pretty)
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

UInventoryView* UInventoryViewLibrary::Make(TArray<UCurrencyView*> Currencies, TArray<UItemGroup*> Items, FOptionalString Scope, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryView>(Outer);
	Serializable->Currencies = Currencies;
	Serializable->Items = Items;
	Serializable->Scope = Scope;
	
	return Serializable;
}

void UInventoryViewLibrary::Break(const UInventoryView* Serializable, TArray<UCurrencyView*>& Currencies, TArray<UItemGroup*>& Items, FOptionalString& Scope)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Currencies = Serializable->Currencies;
		Items = Serializable->Items;
		Scope = Serializable->Scope;
	}
		
}

