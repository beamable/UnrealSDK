
#include "BeamableCore/Public/AutoGen/EventContentResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventContentResponseLibrary::EventContentResponseToJsonString(const UEventContentResponse* Serializable, const bool Pretty)
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

UEventContentResponse* UEventContentResponseLibrary::Make(TArray<UEvent*> Content, UObject* Outer)
{
	auto Serializable = NewObject<UEventContentResponse>(Outer);
	Serializable->Content = Content;
	
	return Serializable;
}

void UEventContentResponseLibrary::Break(const UEventContentResponse* Serializable, TArray<UEvent*>& Content)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Content = Serializable->Content;
	}
		
}

