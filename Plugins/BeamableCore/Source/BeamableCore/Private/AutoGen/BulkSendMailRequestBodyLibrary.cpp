
#include "BeamableCore/Public/AutoGen/BulkSendMailRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBulkSendMailRequestBodyLibrary::BulkSendMailRequestBodyToJsonString(const UBulkSendMailRequestBody* Serializable, const bool Pretty)
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

UBulkSendMailRequestBody* UBulkSendMailRequestBodyLibrary::Make(TArray<USendMailRequestBody*> SendMailRequests, UObject* Outer)
{
	auto Serializable = NewObject<UBulkSendMailRequestBody>(Outer);
	Serializable->SendMailRequests = SendMailRequests;
	
	return Serializable;
}

void UBulkSendMailRequestBodyLibrary::Break(const UBulkSendMailRequestBody* Serializable, TArray<USendMailRequestBody*>& SendMailRequests)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SendMailRequests = Serializable->SendMailRequests;
	}
		
}

