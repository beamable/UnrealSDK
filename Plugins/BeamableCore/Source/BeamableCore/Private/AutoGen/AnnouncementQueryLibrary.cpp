
#include "BeamableCore/Public/AutoGen/AnnouncementQueryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAnnouncementQueryLibrary::AnnouncementQueryToJsonString(const UAnnouncementQuery* Serializable, const bool Pretty)
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

UAnnouncementQuery* UAnnouncementQueryLibrary::Make(FOptionalBool bIncludeDeleted, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementQuery>(Outer);
	Serializable->bIncludeDeleted = bIncludeDeleted;
	
	return Serializable;
}

void UAnnouncementQueryLibrary::Break(const UAnnouncementQuery* Serializable, FOptionalBool& bIncludeDeleted)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIncludeDeleted = Serializable->bIncludeDeleted;
	}
		
}

