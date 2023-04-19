
#include "BeamableCore/Public/AutoGen/InventoryUpdateRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UInventoryUpdateRequestBodyLibrary::InventoryUpdateRequestBodyToJsonString(const UInventoryUpdateRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UInventoryUpdateRequestBody* UInventoryUpdateRequestBodyLibrary::Make(bool bEmpty, TArray<FString> CurrencyContentIds, TArray<FString> ItemContentIds, FOptionalBool bApplyVipBonus, FOptionalString Transaction, FOptionalArrayOfItemUpdateRequestBody UpdateItems, FOptionalArrayOfItemCreateRequestBody NewItems, FOptionalArrayOfItemDeleteRequestBody DeleteItems, FOptionalMapOfInt64 Currencies, FOptionalMapOfArrayOfCurrencyProperty CurrencyProperties, UObject* Outer)
{
	auto Serializable = NewObject<UInventoryUpdateRequestBody>(Outer);
	Serializable->bEmpty = bEmpty;
	Serializable->CurrencyContentIds = CurrencyContentIds;
	Serializable->ItemContentIds = ItemContentIds;
	Serializable->bApplyVipBonus = bApplyVipBonus;
	Serializable->Transaction = Transaction;
	Serializable->UpdateItems = UpdateItems;
	Serializable->NewItems = NewItems;
	Serializable->DeleteItems = DeleteItems;
	Serializable->Currencies = Currencies;
	Serializable->CurrencyProperties = CurrencyProperties;
	
	return Serializable;
}

void UInventoryUpdateRequestBodyLibrary::Break(const UInventoryUpdateRequestBody* Serializable, bool& bEmpty, TArray<FString>& CurrencyContentIds, TArray<FString>& ItemContentIds, FOptionalBool& bApplyVipBonus, FOptionalString& Transaction, FOptionalArrayOfItemUpdateRequestBody& UpdateItems, FOptionalArrayOfItemCreateRequestBody& NewItems, FOptionalArrayOfItemDeleteRequestBody& DeleteItems, FOptionalMapOfInt64& Currencies, FOptionalMapOfArrayOfCurrencyProperty& CurrencyProperties)
{
	bEmpty = Serializable->bEmpty;
	CurrencyContentIds = Serializable->CurrencyContentIds;
	ItemContentIds = Serializable->ItemContentIds;
	bApplyVipBonus = Serializable->bApplyVipBonus;
	Transaction = Serializable->Transaction;
	UpdateItems = Serializable->UpdateItems;
	NewItems = Serializable->NewItems;
	DeleteItems = Serializable->DeleteItems;
	Currencies = Serializable->Currencies;
	CurrencyProperties = Serializable->CurrencyProperties;
		
}

