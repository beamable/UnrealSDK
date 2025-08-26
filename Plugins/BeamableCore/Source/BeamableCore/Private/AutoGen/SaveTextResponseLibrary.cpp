
#include "BeamableCore/Public/AutoGen/SaveTextResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USaveTextResponseLibrary::SaveTextResponseToJsonString(const USaveTextResponse* Serializable, const bool Pretty)
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

USaveTextResponse* USaveTextResponseLibrary::Make(TArray<UTextReference*> Text, UObject* Outer)
{
	auto Serializable = NewObject<USaveTextResponse>(Outer);
	Serializable->Text = Text;
	
	return Serializable;
}

void USaveTextResponseLibrary::Break(const USaveTextResponse* Serializable, TArray<UTextReference*>& Text)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Text = Serializable->Text;
	}
		
}

