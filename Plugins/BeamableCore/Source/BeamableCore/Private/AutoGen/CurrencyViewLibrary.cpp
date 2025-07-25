
#include "BeamableCore/Public/AutoGen/CurrencyViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCurrencyViewLibrary::CurrencyViewToJsonString(const UCurrencyView* Serializable, const bool Pretty)
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

UCurrencyView* UCurrencyViewLibrary::Make(FString Id, int64 Amount, TArray<UCurrencyProperty*> Properties, FOptionalFederationInfo Proxy, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyView>(Outer);
	Serializable->Id = Id;
	Serializable->Amount = Amount;
	Serializable->Properties = Properties;
	Serializable->Proxy = Proxy;
	
	return Serializable;
}

void UCurrencyViewLibrary::Break(const UCurrencyView* Serializable, FString& Id, int64& Amount, TArray<UCurrencyProperty*>& Properties, FOptionalFederationInfo& Proxy)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Amount = Serializable->Amount;
		Properties = Serializable->Properties;
		Proxy = Serializable->Proxy;
	}
		
}

