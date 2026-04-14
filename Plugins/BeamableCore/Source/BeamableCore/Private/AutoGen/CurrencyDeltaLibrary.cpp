
#include "BeamableCore/Public/AutoGen/CurrencyDeltaLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCurrencyDeltaLibrary::CurrencyDeltaToJsonString(const UCurrencyDelta* Serializable, const bool Pretty)
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

UCurrencyDelta* UCurrencyDeltaLibrary::Make(int64 Before, int64 After, FOptionalMapOfPropertyDelta Properties, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyDelta>(Outer);
	Serializable->Before = Before;
	Serializable->After = After;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UCurrencyDeltaLibrary::Break(const UCurrencyDelta* Serializable, int64& Before, int64& After, FOptionalMapOfPropertyDelta& Properties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Before = Serializable->Before;
		After = Serializable->After;
		Properties = Serializable->Properties;
	}
		
}

