
#include "BeamableCore/Public/AutoGen/AnnouncementRawResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAnnouncementRawResponseLibrary::AnnouncementRawResponseToJsonString(const UAnnouncementRawResponse* Serializable, const bool Pretty)
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

UAnnouncementRawResponse* UAnnouncementRawResponseLibrary::Make(TMap<FString, UAnnouncementState*> Announcements, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementRawResponse>(Outer);
	Serializable->Announcements = Announcements;
	
	return Serializable;
}

void UAnnouncementRawResponseLibrary::Break(const UAnnouncementRawResponse* Serializable, TMap<FString, UAnnouncementState*>& Announcements)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Announcements = Serializable->Announcements;
	}
		
}

