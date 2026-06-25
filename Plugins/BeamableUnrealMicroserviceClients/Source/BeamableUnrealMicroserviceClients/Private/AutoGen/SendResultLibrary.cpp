
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendResultLibrary::SendResultToJsonString(const USendResult* Serializable, const bool Pretty)
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

USendResult* USendResultLibrary::Make(int32 Attempted, int32 Succeeded, int32 Failed, bool bSuccess, TArray<FString> Messages, UObject* Outer)
{
	auto Serializable = NewObject<USendResult>(Outer);
	Serializable->Attempted = Attempted;
	Serializable->Succeeded = Succeeded;
	Serializable->Failed = Failed;
	Serializable->bSuccess = bSuccess;
	Serializable->Messages = Messages;
	
	return Serializable;
}

void USendResultLibrary::Break(const USendResult* Serializable, int32& Attempted, int32& Succeeded, int32& Failed, bool& bSuccess, TArray<FString>& Messages)
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

