
#include "BeamableCore/Public/AutoGen/CompletePurchaseRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCompletePurchaseRequestBodyLibrary::CompletePurchaseRequestBodyToJsonString(const UCompletePurchaseRequestBody* Serializable, const bool Pretty)
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

UCompletePurchaseRequestBody* UCompletePurchaseRequestBodyLibrary::Make(int64 Txid, FString Receipt, FString PriceInLocalCurrency, FString IsoCurrencySymbol, UObject* Outer)
{
	auto Serializable = NewObject<UCompletePurchaseRequestBody>(Outer);
	Serializable->Txid = Txid;
	Serializable->Receipt = Receipt;
	Serializable->PriceInLocalCurrency = PriceInLocalCurrency;
	Serializable->IsoCurrencySymbol = IsoCurrencySymbol;
	
	return Serializable;
}

void UCompletePurchaseRequestBodyLibrary::Break(const UCompletePurchaseRequestBody* Serializable, int64& Txid, FString& Receipt, FString& PriceInLocalCurrency, FString& IsoCurrencySymbol)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Txid = Serializable->Txid;
		Receipt = Serializable->Receipt;
		PriceInLocalCurrency = Serializable->PriceInLocalCurrency;
		IsoCurrencySymbol = Serializable->IsoCurrencySymbol;
	}
		
}

