
#include "BeamableCore/Public/AutoGen/AnnouncementAttachmentLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAnnouncementAttachmentLibrary::AnnouncementAttachmentToJsonString(const UAnnouncementAttachment* Serializable, const bool Pretty)
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

UAnnouncementAttachment* UAnnouncementAttachmentLibrary::Make(FString Symbol, int32 Count, FOptionalString Type, FOptionalArrayOfAttachmentProperty Properties, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementAttachment>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->Count = Count;
	Serializable->Type = Type;
	Serializable->Properties = Properties;
	
	return Serializable;
}

void UAnnouncementAttachmentLibrary::Break(const UAnnouncementAttachment* Serializable, FString& Symbol, int32& Count, FOptionalString& Type, FOptionalArrayOfAttachmentProperty& Properties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		Count = Serializable->Count;
		Type = Serializable->Type;
		Properties = Serializable->Properties;
	}
		
}

