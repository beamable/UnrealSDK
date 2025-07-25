
#include "BeamableCore/Public/AutoGen/UpdateMailRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdateMailRequestBodyLibrary::UpdateMailRequestBodyToJsonString(const UUpdateMailRequestBody* Serializable, const bool Pretty)
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

UUpdateMailRequestBody* UUpdateMailRequestBodyLibrary::Make(int64 MailId, FOptionalBool bAcceptAttachments, FOptionalString Body, FOptionalString Expires, FOptionalString Subject, FOptionalString State, FOptionalString Category, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateMailRequestBody>(Outer);
	Serializable->MailId = MailId;
	Serializable->bAcceptAttachments = bAcceptAttachments;
	Serializable->Body = Body;
	Serializable->Expires = Expires;
	Serializable->Subject = Subject;
	Serializable->State = State;
	Serializable->Category = Category;
	
	return Serializable;
}

void UUpdateMailRequestBodyLibrary::Break(const UUpdateMailRequestBody* Serializable, int64& MailId, FOptionalBool& bAcceptAttachments, FOptionalString& Body, FOptionalString& Expires, FOptionalString& Subject, FOptionalString& State, FOptionalString& Category)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MailId = Serializable->MailId;
		bAcceptAttachments = Serializable->bAcceptAttachments;
		Body = Serializable->Body;
		Expires = Serializable->Expires;
		Subject = Serializable->Subject;
		State = Serializable->State;
		Category = Serializable->Category;
	}
		
}

