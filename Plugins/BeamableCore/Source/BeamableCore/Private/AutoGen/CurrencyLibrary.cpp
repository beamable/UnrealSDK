
#include "BeamableCore/Public/AutoGen/CurrencyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCurrencyLibrary::CurrencyToJsonString(const UCurrency* Serializable, const bool Pretty)
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

UCurrency* UCurrencyLibrary::Make(int64 Amount, FString Id, FOptionalInt64 UpdatedAt, FOptionalFederationInfo Proxy, FOptionalArrayOfCurrencyProperty Properties, UObject* Outer)
{
	auto Serializable = NewObject<UCurrency>(Outer);
	Serializable->Amount = Amount;
	Serializable->Id = Id;
	Serializable->UpdatedAt = UpdatedAt;
	Serializable->Proxy = Proxy;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UCurrencyLibrary::Break(const UCurrency* Serializable, int64& Amount, FString& Id, FOptionalInt64& UpdatedAt, FOptionalFederationInfo& Proxy, FOptionalArrayOfCurrencyProperty& Properties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Amount = Serializable->Amount;
		Id = Serializable->Id;
		UpdatedAt = Serializable->UpdatedAt;
		Proxy = Serializable->Proxy;
		Properties = Serializable->Properties;
	}
		
}

