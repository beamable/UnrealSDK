
#include "BeamableCore/Public/AutoGen/AnnouncementQueryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAnnouncementQueryResponseLibrary::AnnouncementQueryResponseToJsonString(const UAnnouncementQueryResponse* Serializable, const bool Pretty)
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

UAnnouncementQueryResponse* UAnnouncementQueryResponseLibrary::Make(TArray<UAnnouncementView*> Announcements, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementQueryResponse>(Outer);
	Serializable->Announcements = Announcements;
	
	return Serializable;
}

void UAnnouncementQueryResponseLibrary::Break(const UAnnouncementQueryResponse* Serializable, TArray<UAnnouncementView*>& Announcements)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Announcements = Serializable->Announcements;
	}
		
}

