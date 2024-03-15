
#include "BeamableCore/Public/AutoGen/SendMsgLibrary.h"

#include "CoreMinimal.h"


FString USendMsgLibrary::SendMsgToJsonString(const USendMsg* Serializable, const bool Pretty)
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

USendMsg* USendMsgLibrary::Make(TArray<int64> To, FOptionalSendNotification Notification, FOptionalMapOfString Data, UObject* Outer)
{
	auto Serializable = NewObject<USendMsg>(Outer);
	Serializable->To = To;
	Serializable->Notification = Notification;
	Serializable->Data = Data;
	
	return Serializable;
}

void USendMsgLibrary::Break(const USendMsg* Serializable, TArray<int64>& To, FOptionalSendNotification& Notification, FOptionalMapOfString& Data)
{
	To = Serializable->To;
	Notification = Serializable->Notification;
	Data = Serializable->Data;
		
}

