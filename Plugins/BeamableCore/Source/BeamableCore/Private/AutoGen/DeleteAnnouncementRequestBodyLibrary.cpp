
#include "BeamableCore/Public/AutoGen/DeleteAnnouncementRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeleteAnnouncementRequestBodyLibrary::DeleteAnnouncementRequestBodyToJsonString(const UDeleteAnnouncementRequestBody* Serializable, const bool Pretty)
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

UDeleteAnnouncementRequestBody* UDeleteAnnouncementRequestBodyLibrary::Make(FString Symbol, UObject* Outer)
{
	auto Serializable = NewObject<UDeleteAnnouncementRequestBody>(Outer);
	Serializable->Symbol = Symbol;
	
	return Serializable;
}

void UDeleteAnnouncementRequestBodyLibrary::Break(const UDeleteAnnouncementRequestBody* Serializable, FString& Symbol)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
	}
		
}

