
#include "AutoGen/CurrencyViewLibrary.h"

#include "CoreMinimal.h"


FString UCurrencyViewLibrary::CurrencyViewToJsonString(const UCurrencyView* Serializable, const bool Pretty)
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

UCurrencyView* UCurrencyViewLibrary::Make(FString Id, int64 Amount, TArray<UCurrencyProperty*> Properties, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyView>(Outer);
	Serializable->Id = Id;
	Serializable->Amount = Amount;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UCurrencyViewLibrary::Break(const UCurrencyView* Serializable, FString& Id, int64& Amount, TArray<UCurrencyProperty*>& Properties)
{
	Id = Serializable->Id;
	Amount = Serializable->Amount;
	Properties = Serializable->Properties;
		
}
