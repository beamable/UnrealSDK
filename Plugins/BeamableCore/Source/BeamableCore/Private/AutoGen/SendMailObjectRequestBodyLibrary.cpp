
#include "BeamableCore/Public/AutoGen/SendMailObjectRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendMailObjectRequestBodyLibrary::SendMailObjectRequestBodyToJsonString(const USendMailObjectRequestBody* Serializable, const bool Pretty)
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

USendMailObjectRequestBody* USendMailObjectRequestBodyLibrary::Make(int64 SenderGamerTag, FString Category, FOptionalString Body, FOptionalString Expires, FOptionalPlayerReward PlayerRewards, FOptionalString Subject, FOptionalMailRewards Rewards, FOptionalInt64 Id, FOptionalInt64 BodyRef, FOptionalArrayOfAttachmentRequestBody Attachments, UObject* Outer)
{
	auto Serializable = NewObject<USendMailObjectRequestBody>(Outer);
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

void USendMailObjectRequestBodyLibrary::Break(const USendMailObjectRequestBody* Serializable, int64& SenderGamerTag, FString& Category, FOptionalString& Body, FOptionalString& Expires, FOptionalPlayerReward& PlayerRewards, FOptionalString& Subject, FOptionalMailRewards& Rewards, FOptionalInt64& Id, FOptionalInt64& BodyRef, FOptionalArrayOfAttachmentRequestBody& Attachments)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
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

