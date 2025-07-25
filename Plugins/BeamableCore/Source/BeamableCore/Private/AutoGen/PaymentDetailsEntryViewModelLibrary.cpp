
#include "BeamableCore/Public/AutoGen/PaymentDetailsEntryViewModelLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPaymentDetailsEntryViewModelLibrary::PaymentDetailsEntryViewModelToJsonString(const UPaymentDetailsEntryViewModel* Serializable, const bool Pretty)
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

UPaymentDetailsEntryViewModel* UPaymentDetailsEntryViewModelLibrary::Make(FString Reference, FString Name, int32 Quantity, FString Sku, int32 Price, FString Gameplace, FString ProviderProductId, FOptionalString Subcategory, FOptionalString LocalPrice, FOptionalString Category, FOptionalString LocalCurrency, UObject* Outer)
{
	auto Serializable = NewObject<UPaymentDetailsEntryViewModel>(Outer);
	Serializable->Reference = Reference;
	Serializable->Name = Name;
	Serializable->Quantity = Quantity;
	Serializable->Sku = Sku;
	Serializable->Price = Price;
	Serializable->Gameplace = Gameplace;
	Serializable->ProviderProductId = ProviderProductId;
	Serializable->Subcategory = Subcategory;
	Serializable->LocalPrice = LocalPrice;
	Serializable->Category = Category;
	Serializable->LocalCurrency = LocalCurrency;
	
	return Serializable;
}

void UPaymentDetailsEntryViewModelLibrary::Break(const UPaymentDetailsEntryViewModel* Serializable, FString& Reference, FString& Name, int32& Quantity, FString& Sku, int32& Price, FString& Gameplace, FString& ProviderProductId, FOptionalString& Subcategory, FOptionalString& LocalPrice, FOptionalString& Category, FOptionalString& LocalCurrency)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Reference = Serializable->Reference;
		Name = Serializable->Name;
		Quantity = Serializable->Quantity;
		Sku = Serializable->Sku;
		Price = Serializable->Price;
		Gameplace = Serializable->Gameplace;
		ProviderProductId = Serializable->ProviderProductId;
		Subcategory = Serializable->Subcategory;
		LocalPrice = Serializable->LocalPrice;
		Category = Serializable->Category;
		LocalCurrency = Serializable->LocalCurrency;
	}
		
}

