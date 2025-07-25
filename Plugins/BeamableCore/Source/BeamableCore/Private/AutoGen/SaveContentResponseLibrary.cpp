
#include "BeamableCore/Public/AutoGen/SaveContentResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USaveContentResponseLibrary::SaveContentResponseToJsonString(const USaveContentResponse* Serializable, const bool Pretty)
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

USaveContentResponse* USaveContentResponseLibrary::Make(TArray<UContentReference*> Content, UObject* Outer)
{
	auto Serializable = NewObject<USaveContentResponse>(Outer);
	Serializable->Content = Content;
	
	return Serializable;
}

void USaveContentResponseLibrary::Break(const USaveContentResponse* Serializable, TArray<UContentReference*>& Content)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Content = Serializable->Content;
	}
		
}

