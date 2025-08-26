
#include "BeamableCore/Public/AutoGen/LocalizedPriceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULocalizedPriceLibrary::LocalizedPriceToJsonString(const ULocalizedPrice* Serializable, const bool Pretty)
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

ULocalizedPrice* ULocalizedPriceLibrary::Make(int64 To, int64 Price, double PriceLocalized, FString PriceLocalizedString, UObject* Outer)
{
	auto Serializable = NewObject<ULocalizedPrice>(Outer);
	Serializable->To = To;
	Serializable->Price = Price;
	Serializable->PriceLocalized = PriceLocalized;
	Serializable->PriceLocalizedString = PriceLocalizedString;
	
	return Serializable;
}

void ULocalizedPriceLibrary::Break(const ULocalizedPrice* Serializable, int64& To, int64& Price, double& PriceLocalized, FString& PriceLocalizedString)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		To = Serializable->To;
		Price = Serializable->Price;
		PriceLocalized = Serializable->PriceLocalized;
		PriceLocalizedString = Serializable->PriceLocalizedString;
	}
		
}

