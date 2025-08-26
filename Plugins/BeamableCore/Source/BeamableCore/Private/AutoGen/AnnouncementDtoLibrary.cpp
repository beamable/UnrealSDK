
#include "BeamableCore/Public/AutoGen/AnnouncementDtoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAnnouncementDtoLibrary::AnnouncementDtoToJsonString(const UAnnouncementDto* Serializable, const bool Pretty)
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

UAnnouncementDto* UAnnouncementDtoLibrary::Make(ULocalizationRef* Body, FString Channel, FString Symbol, ULocalizationRef* Title, ULocalizationRef* Summary, FOptionalString StartDate, FOptionalPlayerReward Gift, FOptionalString EndDate, FOptionalArrayOfString Tags, FOptionalArrayOfPlayerStatRequirement StatRequirements, FOptionalArrayOfAnnouncementAttachment Attachments, FOptionalMapOfString ClientData, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementDto>(Outer);
	Serializable->Body = Body;
	Serializable->Channel = Channel;
	Serializable->Symbol = Symbol;
	Serializable->Title = Title;
	Serializable->Summary = Summary;
	Serializable->StartDate = StartDate;
	Serializable->Gift = Gift;
	Serializable->EndDate = EndDate;
	Serializable->Tags = Tags;
	Serializable->StatRequirements = StatRequirements;
	Serializable->Attachments = Attachments;
	Serializable->ClientData = ClientData;
	
	return Serializable;
}

void UAnnouncementDtoLibrary::Break(const UAnnouncementDto* Serializable, ULocalizationRef*& Body, FString& Channel, FString& Symbol, ULocalizationRef*& Title, ULocalizationRef*& Summary, FOptionalString& StartDate, FOptionalPlayerReward& Gift, FOptionalString& EndDate, FOptionalArrayOfString& Tags, FOptionalArrayOfPlayerStatRequirement& StatRequirements, FOptionalArrayOfAnnouncementAttachment& Attachments, FOptionalMapOfString& ClientData)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Body = Serializable->Body;
		Channel = Serializable->Channel;
		Symbol = Serializable->Symbol;
		Title = Serializable->Title;
		Summary = Serializable->Summary;
		StartDate = Serializable->StartDate;
		Gift = Serializable->Gift;
		EndDate = Serializable->EndDate;
		Tags = Serializable->Tags;
		StatRequirements = Serializable->StatRequirements;
		Attachments = Serializable->Attachments;
		ClientData = Serializable->ClientData;
	}
		
}

