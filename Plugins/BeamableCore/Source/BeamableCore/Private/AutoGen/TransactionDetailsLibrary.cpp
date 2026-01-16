
#include "BeamableCore/Public/AutoGen/TransactionDetailsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTransactionDetailsLibrary::TransactionDetailsToJsonString(const UTransactionDetails* Serializable, const bool Pretty)
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

UTransactionDetails* UTransactionDetailsLibrary::Make(int32 PriceCents, FString Sku, FString ProviderProductId, FOptionalInt32 Quantity, FOptionalString Name, FOptionalString Reference, FOptionalString GamePlace, FOptionalString Category, FOptionalString Subcategory, FOptionalString LocalCurrency, FOptionalString LocalPrice, UObject* Outer)
{
	auto Serializable = NewObject<UTransactionDetails>(Outer);
	Serializable->PriceCents = PriceCents;
	Serializable->Sku = Sku;
	Serializable->ProviderProductId = ProviderProductId;
	Serializable->Quantity = Quantity;
	Serializable->Name = Name;
	Serializable->Reference = Reference;
	Serializable->GamePlace = GamePlace;
	Serializable->Category = Category;
	Serializable->Subcategory = Subcategory;
	Serializable->LocalCurrency = LocalCurrency;
	Serializable->LocalPrice = LocalPrice;
	
	return Serializable;
}

void UTransactionDetailsLibrary::Break(const UTransactionDetails* Serializable, int32& PriceCents, FString& Sku, FString& ProviderProductId, FOptionalInt32& Quantity, FOptionalString& Name, FOptionalString& Reference, FOptionalString& GamePlace, FOptionalString& Category, FOptionalString& Subcategory, FOptionalString& LocalCurrency, FOptionalString& LocalPrice)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PriceCents = Serializable->PriceCents;
		Sku = Serializable->Sku;
		ProviderProductId = Serializable->ProviderProductId;
		Quantity = Serializable->Quantity;
		Name = Serializable->Name;
		Reference = Serializable->Reference;
		GamePlace = Serializable->GamePlace;
		Category = Serializable->Category;
		Subcategory = Serializable->Subcategory;
		LocalCurrency = Serializable->LocalCurrency;
		LocalPrice = Serializable->LocalPrice;
	}
		
}

