
#include "BeamableCore/Public/AutoGen/CurrencyContentResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCurrencyContentResponseLibrary::CurrencyContentResponseToJsonString(const UCurrencyContentResponse* Serializable, const bool Pretty)
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

UCurrencyContentResponse* UCurrencyContentResponseLibrary::Make(TArray<UCurrencyArchetype*> Content, UObject* Outer)
{
	auto Serializable = NewObject<UCurrencyContentResponse>(Outer);
	Serializable->Content = Content;
	
	return Serializable;
}

void UCurrencyContentResponseLibrary::Break(const UCurrencyContentResponse* Serializable, TArray<UCurrencyArchetype*>& Content)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Content = Serializable->Content;
	}
		
}

