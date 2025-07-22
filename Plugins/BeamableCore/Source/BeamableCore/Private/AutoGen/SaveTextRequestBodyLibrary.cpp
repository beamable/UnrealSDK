
#include "BeamableCore/Public/AutoGen/SaveTextRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USaveTextRequestBodyLibrary::SaveTextRequestBodyToJsonString(const USaveTextRequestBody* Serializable, const bool Pretty)
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

USaveTextRequestBody* USaveTextRequestBodyLibrary::Make(TArray<UTextDefinition*> Text, UObject* Outer)
{
	auto Serializable = NewObject<USaveTextRequestBody>(Outer);
	Serializable->Text = Text;
	
	return Serializable;
}

void USaveTextRequestBodyLibrary::Break(const USaveTextRequestBody* Serializable, TArray<UTextDefinition*>& Text)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Text = Serializable->Text;
	}
		
}

