
#include "BeamableCore/Public/AutoGen/CurrencyPropertyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCurrencyPropertyLibrary::CurrencyPropertyToJsonString(const UCurrencyProperty* Serializable, const bool Pretty)
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

UCurrencyProperty* UCurrencyPropertyLibrary::Make(FString Name, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyProperty>(Outer);
	Serializable->Name = Name;
	Serializable->Value = Value;
	
	return Serializable;
}

void UCurrencyPropertyLibrary::Break(const UCurrencyProperty* Serializable, FString& Name, FString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Value = Serializable->Value;
	}
		
}

