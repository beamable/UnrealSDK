
#include "BeamableCore/Public/AutoGen/SendMailRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendMailRequestBodyLibrary::SendMailRequestBodyToJsonString(const USendMailRequestBody* Serializable, const bool Pretty)
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

USendMailRequestBody* USendMailRequestBodyLibrary::Make(int64 ReceiverGamerTag, int64 SenderGamerTag, FString Category, FOptionalString Body, FOptionalString Expires, FOptionalPlayerReward PlayerRewards, FOptionalString Subject, FOptionalMailRewards Rewards, FOptionalInt64 Id, FOptionalInt64 BodyRef, FOptionalArrayOfAttachmentRequestBody Attachments, UObject* Outer)
{
	auto Serializable = NewObject<USendMailRequestBody>(Outer);
	Serializable->ReceiverGamerTag = ReceiverGamerTag;
	Serializable->SenderGamerTag = SenderGamerTag;
	Serializable->Category = Category;
	Serializable->Body = Body;
	Serializable->Expires = Expires;
	Serializable->PlayerRewards = PlayerRewards;
	Serializable->Subject = Subject;
	Serializable->Rewards = Rewards;
	Serializable->Id = Id;
	Serializable->BodyRef = BodyRef;
	Serializable->Attachments = Attachments;
	
	return Serializable;
}

void USendMailRequestBodyLibrary::Break(const USendMailRequestBody* Serializable, int64& ReceiverGamerTag, int64& SenderGamerTag, FString& Category, FOptionalString& Body, FOptionalString& Expires, FOptionalPlayerReward& PlayerRewards, FOptionalString& Subject, FOptionalMailRewards& Rewards, FOptionalInt64& Id, FOptionalInt64& BodyRef, FOptionalArrayOfAttachmentRequestBody& Attachments)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ReceiverGamerTag = Serializable->ReceiverGamerTag;
		SenderGamerTag = Serializable->SenderGamerTag;
		Category = Serializable->Category;
		Body = Serializable->Body;
		Expires = Serializable->Expires;
		PlayerRewards = Serializable->PlayerRewards;
		Subject = Serializable->Subject;
		Rewards = Serializable->Rewards;
		Id = Serializable->Id;
		BodyRef = Serializable->BodyRef;
		Attachments = Serializable->Attachments;
	}
		
}

