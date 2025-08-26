
#include "BeamableCore/Public/AutoGen/AcceptMultipleAttachmentsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAcceptMultipleAttachmentsLibrary::AcceptMultipleAttachmentsToJsonString(const UAcceptMultipleAttachments* Serializable, const bool Pretty)
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

UAcceptMultipleAttachments* UAcceptMultipleAttachmentsLibrary::Make(TArray<int64> MailIds, UObject* Outer)
{
	auto Serializable = NewObject<UAcceptMultipleAttachments>(Outer);
	Serializable->MailIds = MailIds;
	
	return Serializable;
}

void UAcceptMultipleAttachmentsLibrary::Break(const UAcceptMultipleAttachments* Serializable, TArray<int64>& MailIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MailIds = Serializable->MailIds;
	}
		
}

