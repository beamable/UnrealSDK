
#include "BeamableCore/Public/AutoGen/TrackPurchaseRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTrackPurchaseRequestBodyLibrary::TrackPurchaseRequestBodyToJsonString(const UTrackPurchaseRequestBody* Serializable, const bool Pretty)
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

UTrackPurchaseRequestBody* UTrackPurchaseRequestBodyLibrary::Make(double PriceInLocalCurrency, FString SkuName, FString SkuProductId, FString Store, FString PurchaseId, FString IsoCurrencySymbol, TArray<UItemCreateRequestBody*> ObtainItems, TArray<UCurrencyChange*> ObtainCurrency, UObject* Outer)
{
	auto Serializable = NewObject<UTrackPurchaseRequestBody>(Outer);
	Serializable->PriceInLocalCurrency = PriceInLocalCurrency;
	Serializable->SkuName = SkuName;
	Serializable->SkuProductId = SkuProductId;
	Serializable->Store = Store;
	Serializable->PurchaseId = PurchaseId;
	Serializable->IsoCurrencySymbol = IsoCurrencySymbol;
	Serializable->ObtainItems = ObtainItems;
	Serializable->ObtainCurrency = ObtainCurrency;
	
	return Serializable;
}

void UTrackPurchaseRequestBodyLibrary::Break(const UTrackPurchaseRequestBody* Serializable, double& PriceInLocalCurrency, FString& SkuName, FString& SkuProductId, FString& Store, FString& PurchaseId, FString& IsoCurrencySymbol, TArray<UItemCreateRequestBody*>& ObtainItems, TArray<UCurrencyChange*>& ObtainCurrency)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PriceInLocalCurrency = Serializable->PriceInLocalCurrency;
		SkuName = Serializable->SkuName;
		SkuProductId = Serializable->SkuProductId;
		Store = Serializable->Store;
		PurchaseId = Serializable->PurchaseId;
		IsoCurrencySymbol = Serializable->IsoCurrencySymbol;
		ObtainItems = Serializable->ObtainItems;
		ObtainCurrency = Serializable->ObtainCurrency;
	}
		
}

