
#include "BeamableCore/Public/AutoGen/HtmlResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UHtmlResponseLibrary::HtmlResponseToJsonString(const UHtmlResponse* Serializable, const bool Pretty)
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

UHtmlResponse* UHtmlResponseLibrary::Make(FString Html, UObject* Outer)
{
	auto Serializable = NewObject<UHtmlResponse>(Outer);
	Serializable->Html = Html;
	
	return Serializable;
}

void UHtmlResponseLibrary::Break(const UHtmlResponse* Serializable, FString& Html)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Html = Serializable->Html;
	}
		
}

