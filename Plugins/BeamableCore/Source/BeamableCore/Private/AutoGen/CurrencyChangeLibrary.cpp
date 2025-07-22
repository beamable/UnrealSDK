
#include "BeamableCore/Public/AutoGen/CurrencyChangeLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCurrencyChangeLibrary::CurrencyChangeToJsonString(const UCurrencyChange* Serializable, const bool Pretty)
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

UCurrencyChange* UCurrencyChangeLibrary::Make(FString Symbol, int64 Amount, FOptionalInt64 OriginalAmount, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyChange>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Amount = Amount;
	Serializable->OriginalAmount = OriginalAmount;
	
	return Serializable;
}

void UCurrencyChangeLibrary::Break(const UCurrencyChange* Serializable, FString& Symbol, int64& Amount, FOptionalInt64& OriginalAmount)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Amount = Serializable->Amount;
		OriginalAmount = Serializable->OriginalAmount;
	}
		
}

