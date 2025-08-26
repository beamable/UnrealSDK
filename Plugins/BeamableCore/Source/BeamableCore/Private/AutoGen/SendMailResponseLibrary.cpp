
#include "BeamableCore/Public/AutoGen/SendMailResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendMailResponseLibrary::SendMailResponseToJsonString(const USendMailResponse* Serializable, const bool Pretty)
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

USendMailResponse* USendMailResponseLibrary::Make(FOptionalInt64 MailId, UObject* Outer)
{
	auto Serializable = NewObject<USendMailResponse>(Outer);
	Serializable->MailId = MailId;
	
	return Serializable;
}

void USendMailResponseLibrary::Break(const USendMailResponse* Serializable, FOptionalInt64& MailId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MailId = Serializable->MailId;
	}
		
}

