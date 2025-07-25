
#include "BeamableCore/Public/AutoGen/AnnouncementRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAnnouncementRequestBodyLibrary::AnnouncementRequestBodyToJsonString(const UAnnouncementRequestBody* Serializable, const bool Pretty)
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

UAnnouncementRequestBody* UAnnouncementRequestBodyLibrary::Make(FOptionalString Announcement, FOptionalArrayOfString Announcements, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementRequestBody>(Outer);
	Serializable->Announcement = Announcement;
	Serializable->Announcements = Announcements;
	
	return Serializable;
}

void UAnnouncementRequestBodyLibrary::Break(const UAnnouncementRequestBody* Serializable, FOptionalString& Announcement, FOptionalArrayOfString& Announcements)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Announcement = Serializable->Announcement;
		Announcements = Serializable->Announcements;
	}
		
}

