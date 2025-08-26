
#include "BeamableCore/Public/AutoGen/AnnouncementViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAnnouncementViewLibrary::AnnouncementViewToJsonString(const UAnnouncementView* Serializable, const bool Pretty)
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

UAnnouncementView* UAnnouncementViewLibrary::Make(bool bIsClaimed, bool bIsDeleted, bool bIsRead, FString Body, FString Channel, FString Id, FString Title, FString Summary, TArray<UClientDataEntry*> ClientDataList, TArray<UAnnouncementAttachment*> Attachments, FOptionalString EndDate, FOptionalPlayerReward Gift, FOptionalInt64 SecondsRemaining, FOptionalString StartDate, FOptionalArrayOfString Tags, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementView>(Outer);
	Serializable->bIsClaimed = bIsClaimed;
	Serializable->bIsDeleted = bIsDeleted;
	Serializable->bIsRead = bIsRead;
	Serializable->Body = Body;
	Serializable->Channel = Channel;
	Serializable->Id = Id;
	Serializable->Title = Title;
	Serializable->Summary = Summary;
	Serializable->ClientDataList = ClientDataList;
	Serializable->Attachments = Attachments;
	Serializable->EndDate = EndDate;
	Serializable->Gift = Gift;
	Serializable->SecondsRemaining = SecondsRemaining;
	Serializable->StartDate = StartDate;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UAnnouncementViewLibrary::Break(const UAnnouncementView* Serializable, bool& bIsClaimed, bool& bIsDeleted, bool& bIsRead, FString& Body, FString& Channel, FString& Id, FString& Title, FString& Summary, TArray<UClientDataEntry*>& ClientDataList, TArray<UAnnouncementAttachment*>& Attachments, FOptionalString& EndDate, FOptionalPlayerReward& Gift, FOptionalInt64& SecondsRemaining, FOptionalString& StartDate, FOptionalArrayOfString& Tags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bIsClaimed = Serializable->bIsClaimed;
		bIsDeleted = Serializable->bIsDeleted;
		bIsRead = Serializable->bIsRead;
		Body = Serializable->Body;
		Channel = Serializable->Channel;
		Id = Serializable->Id;
		Title = Serializable->Title;
		Summary = Serializable->Summary;
		ClientDataList = Serializable->ClientDataList;
		Attachments = Serializable->Attachments;
		EndDate = Serializable->EndDate;
		Gift = Serializable->Gift;
		SecondsRemaining = Serializable->SecondsRemaining;
		StartDate = Serializable->StartDate;
		Tags = Serializable->Tags;
	}
		
}

