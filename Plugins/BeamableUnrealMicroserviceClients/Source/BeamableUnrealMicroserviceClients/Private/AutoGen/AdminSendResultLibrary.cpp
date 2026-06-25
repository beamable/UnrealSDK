
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AdminSendResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAdminSendResultLibrary::AdminSendResultToJsonString(const UAdminSendResult* Serializable, const bool Pretty)
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

UAdminSendResult* UAdminSendResultLibrary::Make(int32 Attempted, int32 Succeeded, int32 Failed, bool bSuccess, TArray<FString> Messages, UObject* Outer)
{
	auto Serializable = NewObject<UAdminSendResult>(Outer);
	Serializable->Attempted = Attempted;
	Serializable->Succeeded = Succeeded;
	Serializable->Failed = Failed;
	Serializable->bSuccess = bSuccess;
	Serializable->Messages = Messages;
	
	return Serializable;
}

void UAdminSendResultLibrary::Break(const UAdminSendResult* Serializable, int32& Attempted, int32& Succeeded, int32& Failed, bool& bSuccess, TArray<FString>& Messages)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Attempted = Serializable->Attempted;
		Succeeded = Serializable->Succeeded;
		Failed = Serializable->Failed;
		bSuccess = Serializable->bSuccess;
		Messages = Serializable->Messages;
	}
		
}

