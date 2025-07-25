
#include "BeamableCore/Public/AutoGen/SearchAnnouncementsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USearchAnnouncementsRequestBodyLibrary::SearchAnnouncementsRequestBodyToJsonString(const USearchAnnouncementsRequestBody* Serializable, const bool Pretty)
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

USearchAnnouncementsRequestBody* USearchAnnouncementsRequestBodyLibrary::Make(FOptionalString Date, UObject* Outer)
{
	auto Serializable = NewObject<USearchAnnouncementsRequestBody>(Outer);
	Serializable->Date = Date;
	
	return Serializable;
}

void USearchAnnouncementsRequestBodyLibrary::Break(const USearchAnnouncementsRequestBody* Serializable, FOptionalString& Date)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Date = Serializable->Date;
	}
		
}

