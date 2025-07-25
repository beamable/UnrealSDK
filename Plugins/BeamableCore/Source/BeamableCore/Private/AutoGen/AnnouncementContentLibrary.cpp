
#include "BeamableCore/Public/AutoGen/AnnouncementContentLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAnnouncementContentLibrary::AnnouncementContentToJsonString(const UAnnouncementContent* Serializable, const bool Pretty)
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

UAnnouncementContent* UAnnouncementContentLibrary::Make(FString Body, FString Channel, FString Symbol, FString Title, FString Summary, FOptionalString StartDate, FOptionalPlayerReward Gift, FOptionalString EndDate, FOptionalArrayOfString Tags, FOptionalArrayOfPlayerStatRequirement StatRequirements, FOptionalArrayOfAnnouncementAttachment Attachments, FOptionalMapOfString ClientData, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementContent>(Outer);
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

void UAnnouncementContentLibrary::Break(const UAnnouncementContent* Serializable, FString& Body, FString& Channel, FString& Symbol, FString& Title, FString& Summary, FOptionalString& StartDate, FOptionalPlayerReward& Gift, FOptionalString& EndDate, FOptionalArrayOfString& Tags, FOptionalArrayOfPlayerStatRequirement& StatRequirements, FOptionalArrayOfAnnouncementAttachment& Attachments, FOptionalMapOfString& ClientData)
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

