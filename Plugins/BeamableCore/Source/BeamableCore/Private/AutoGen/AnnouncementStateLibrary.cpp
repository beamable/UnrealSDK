
#include "BeamableCore/Public/AutoGen/AnnouncementStateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAnnouncementStateLibrary::AnnouncementStateToJsonString(const UAnnouncementState* Serializable, const bool Pretty)
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

UAnnouncementState* UAnnouncementStateLibrary::Make(bool bIsClaimed, bool bIsDeleted, bool bIsRead, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementState>(Outer);
	Serializable->bIsClaimed = bIsClaimed;
	Serializable->bIsDeleted = bIsDeleted;
	Serializable->bIsRead = bIsRead;
	
	return Serializable;
}

void UAnnouncementStateLibrary::Break(const UAnnouncementState* Serializable, bool& bIsClaimed, bool& bIsDeleted, bool& bIsRead)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsClaimed = Serializable->bIsClaimed;
		bIsDeleted = Serializable->bIsDeleted;
		bIsRead = Serializable->bIsRead;
	}
		
}

