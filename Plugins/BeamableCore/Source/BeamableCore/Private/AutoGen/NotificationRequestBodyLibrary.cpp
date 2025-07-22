
#include "BeamableCore/Public/AutoGen/NotificationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UNotificationRequestBodyLibrary::NotificationRequestBodyToJsonString(const UNotificationRequestBody* Serializable, const bool Pretty)
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

UNotificationRequestBody* UNotificationRequestBodyLibrary::Make(UNotificationRequestData* Payload, FOptionalBool bUseSignalWhenPossible, FOptionalString CustomChannelSuffix, FOptionalInt64 Dbid, FOptionalArrayOfInt64 Dbids, UObject* Outer)
{
	auto Serializable = NewObject<UNotificationRequestBody>(Outer);
	Serializable->Payload = Payload;
	Serializable->bUseSignalWhenPossible = bUseSignalWhenPossible;
	Serializable->CustomChannelSuffix = CustomChannelSuffix;
	Serializable->Dbid = Dbid;
	Serializable->Dbids = Dbids;
	
	return Serializable;
}

void UNotificationRequestBodyLibrary::Break(const UNotificationRequestBody* Serializable, UNotificationRequestData*& Payload, FOptionalBool& bUseSignalWhenPossible, FOptionalString& CustomChannelSuffix, FOptionalInt64& Dbid, FOptionalArrayOfInt64& Dbids)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Payload = Serializable->Payload;
		bUseSignalWhenPossible = Serializable->bUseSignalWhenPossible;
		CustomChannelSuffix = Serializable->CustomChannelSuffix;
		Dbid = Serializable->Dbid;
		Dbids = Serializable->Dbids;
	}
		
}

