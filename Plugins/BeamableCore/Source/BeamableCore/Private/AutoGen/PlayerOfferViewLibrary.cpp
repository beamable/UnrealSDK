
#include "BeamableCore/Public/AutoGen/PlayerOfferViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayerOfferViewLibrary::PlayerOfferViewToJsonString(const UPlayerOfferView* Serializable, const bool Pretty)
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

UPlayerOfferView* UPlayerOfferViewLibrary::Make(int32 Coupons, UPrice* Price, FString Symbol, TArray<FString> Titles, TArray<UItemCreateRequestBody*> ObtainItems, TArray<UCurrencyChange*> ObtainCurrency, TArray<FString> Images, TArray<FString> Descriptions, TArray<FString> Obtain, FOptionalString ButtonText, UObject* Outer)
{
	auto Serializable = NewObject<UPlayerOfferView>(Outer);
	Serializable->Coupons = Coupons;
	Serializable->Price = Price;
	Serializable->Symbol = Symbol;
	Serializable->Titles = Titles;
	Serializable->ObtainItems = ObtainItems;
	Serializable->ObtainCurrency = ObtainCurrency;
	Serializable->Images = Images;
	Serializable->Descriptions = Descriptions;
	Serializable->Obtain = Obtain;
	Serializable->ButtonText = ButtonText;
	
	return Serializable;
}

void UPlayerOfferViewLibrary::Break(const UPlayerOfferView* Serializable, int32& Coupons, UPrice*& Price, FString& Symbol, TArray<FString>& Titles, TArray<UItemCreateRequestBody*>& ObtainItems, TArray<UCurrencyChange*>& ObtainCurrency, TArray<FString>& Images, TArray<FString>& Descriptions, TArray<FString>& Obtain, FOptionalString& ButtonText)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Coupons = Serializable->Coupons;
		Price = Serializable->Price;
		Symbol = Serializable->Symbol;
		Titles = Serializable->Titles;
		ObtainItems = Serializable->ObtainItems;
		ObtainCurrency = Serializable->ObtainCurrency;
		Images = Serializable->Images;
		Descriptions = Serializable->Descriptions;
		Obtain = Serializable->Obtain;
		ButtonText = Serializable->ButtonText;
	}
		
}

