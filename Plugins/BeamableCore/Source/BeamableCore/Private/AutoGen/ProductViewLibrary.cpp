
#include "BeamableCore/Public/AutoGen/ProductViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UProductViewLibrary::ProductViewToJsonString(const UProductView* Serializable, const bool Pretty)
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

UProductView* UProductViewLibrary::Make(double LocalizedPrice, FString Sku, FString Description, FString IsoCurrencyCode, FString LocalizedPriceString, UObject* Outer)
{
	auto Serializable = NewObject<UProductView>(Outer);
	Serializable->LocalizedPrice = LocalizedPrice;
	Serializable->Sku = Sku;
	Serializable->Description = Description;
	Serializable->IsoCurrencyCode = IsoCurrencyCode;
	Serializable->LocalizedPriceString = LocalizedPriceString;
	
	return Serializable;
}

void UProductViewLibrary::Break(const UProductView* Serializable, double& LocalizedPrice, FString& Sku, FString& Description, FString& IsoCurrencyCode, FString& LocalizedPriceString)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		LocalizedPrice = Serializable->LocalizedPrice;
		Sku = Serializable->Sku;
		Description = Serializable->Description;
		IsoCurrencyCode = Serializable->IsoCurrencyCode;
		LocalizedPriceString = Serializable->LocalizedPriceString;
	}
		
}

