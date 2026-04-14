
#include "BeamableCore/Public/AutoGen/SessionBasicStartSessionRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionBasicStartSessionRequestBodyLibrary::SessionBasicStartSessionRequestBodyToJsonString(const USessionBasicStartSessionRequestBody* Serializable, const bool Pretty)
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

USessionBasicStartSessionRequestBody* USessionBasicStartSessionRequestBodyLibrary::Make(FOptionalString Source, FOptionalString Shard, FOptionalString Locale, FOptionalSessionLanguageContext Language, FOptionalInt64 Time, FOptionalString Platform, FOptionalInt64 Gamer, FOptionalString Device, FOptionalMapOfString CustomParams, FOptionalMapOfString DeviceParams, UObject* Outer)
{
	auto Serializable = NewObject<USessionBasicStartSessionRequestBody>(Outer);
	Serializable->Source = Source;
	Serializable->Shard = Shard;
	Serializable->Locale = Locale;
	Serializable->Language = Language;
	Serializable->Time = Time;
	Serializable->Platform = Platform;
	Serializable->Gamer = Gamer;
	Serializable->Device = Device;
	Serializable->CustomParams = CustomParams;
	Serializable->DeviceParams = DeviceParams;
	
	return Serializable;
}

void USessionBasicStartSessionRequestBodyLibrary::Break(const USessionBasicStartSessionRequestBody* Serializable, FOptionalString& Source, FOptionalString& Shard, FOptionalString& Locale, FOptionalSessionLanguageContext& Language, FOptionalInt64& Time, FOptionalString& Platform, FOptionalInt64& Gamer, FOptionalString& Device, FOptionalMapOfString& CustomParams, FOptionalMapOfString& DeviceParams)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Source = Serializable->Source;
		Shard = Serializable->Shard;
		Locale = Serializable->Locale;
		Language = Serializable->Language;
		Time = Serializable->Time;
		Platform = Serializable->Platform;
		Gamer = Serializable->Gamer;
		Device = Serializable->Device;
		CustomParams = Serializable->CustomParams;
		DeviceParams = Serializable->DeviceParams;
	}
		
}

