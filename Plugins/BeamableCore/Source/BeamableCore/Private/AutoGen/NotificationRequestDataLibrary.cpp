
#include "BeamableCore/Public/AutoGen/NotificationRequestDataLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UNotificationRequestDataLibrary::NotificationRequestDataToJsonString(const UNotificationRequestData* Serializable, const bool Pretty)
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

UNotificationRequestData* UNotificationRequestDataLibrary::Make(FOptionalString Channel, FOptionalString MessageKey, FOptionalString Context, FOptionalString Shard, FOptionalString MessageFull, FOptionalArrayOfString MessageParams, FOptionalMapOfString Meta, UObject* Outer)
{
	auto Serializable = NewObject<UNotificationRequestData>(Outer);
	Serializable->Channel = Channel;
	Serializable->MessageKey = MessageKey;
	Serializable->Context = Context;
	Serializable->Shard = Shard;
	Serializable->MessageFull = MessageFull;
	Serializable->MessageParams = MessageParams;
	Serializable->Meta = Meta;
	
	return Serializable;
}

void UNotificationRequestDataLibrary::Break(const UNotificationRequestData* Serializable, FOptionalString& Channel, FOptionalString& MessageKey, FOptionalString& Context, FOptionalString& Shard, FOptionalString& MessageFull, FOptionalArrayOfString& MessageParams, FOptionalMapOfString& Meta)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Channel = Serializable->Channel;
		MessageKey = Serializable->MessageKey;
		Context = Serializable->Context;
		Shard = Serializable->Shard;
		MessageFull = Serializable->MessageFull;
		MessageParams = Serializable->MessageParams;
		Meta = Serializable->Meta;
	}
		
}

