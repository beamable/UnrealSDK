
#include "BeamableCore/Public/AutoGen/SaveSKUsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USaveSKUsRequestBodyLibrary::SaveSKUsRequestBodyToJsonString(const USaveSKUsRequestBody* Serializable, const bool Pretty)
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

USaveSKUsRequestBody* USaveSKUsRequestBodyLibrary::Make(TArray<USKU*> Definitions, UObject* Outer)
{
	auto Serializable = NewObject<USaveSKUsRequestBody>(Outer);
	Serializable->Definitions = Definitions;
	
	return Serializable;
}

void USaveSKUsRequestBodyLibrary::Break(const USaveSKUsRequestBody* Serializable, TArray<USKU*>& Definitions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Definitions = Serializable->Definitions;
	}
		
}

