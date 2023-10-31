
#include "BeamableCore/Public/AutoGen/CurrencyLibrary.h"

#include "CoreMinimal.h"


FString UCurrencyLibrary::CurrencyToJsonString(const UCurrency* Serializable, const bool Pretty)
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

UCurrency* UCurrencyLibrary::Make(FString Id, int64 Amount, FOptionalArchetypeProxy Proxy, FOptionalArrayOfCurrencyProperty Properties, UObject* Outer)
{
	auto Serializable = NewObject<UCurrency>(Outer);
	Serializable->Id = Id;
	Serializable->Amount = Amount;
	Serializable->Proxy = Proxy;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UCurrencyLibrary::Break(const UCurrency* Serializable, FString& Id, int64& Amount, FOptionalArchetypeProxy& Proxy, FOptionalArrayOfCurrencyProperty& Properties)
{
	Id = Serializable->Id;
	Amount = Serializable->Amount;
	Proxy = Serializable->Proxy;
	Properties = Serializable->Properties;
		
}

