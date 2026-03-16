
#include "BeamableCore/Public/AutoGen/SessionActorStartSessionRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionActorStartSessionRequestBodyLibrary::SessionActorStartSessionRequestBodyToJsonString(const USessionActorStartSessionRequestBody* Serializable, const bool Pretty)
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

USessionActorStartSessionRequestBody* USessionActorStartSessionRequestBodyLibrary::Make(FOptionalString Platform, FOptionalString Device, FOptionalString Source, FOptionalString Locale, FOptionalSessionLanguageContextDto Language, FOptionalMapOfString CustomParams, UObject* Outer)
{
	auto Serializable = NewObject<USessionActorStartSessionRequestBody>(Outer);
	Serializable->Platform = Platform;
	Serializable->Device = Device;
	Serializable->Source = Source;
	Serializable->Locale = Locale;
	Serializable->Language = Language;
	Serializable->CustomParams = CustomParams;
	
	return Serializable;
}

void USessionActorStartSessionRequestBodyLibrary::Break(const USessionActorStartSessionRequestBody* Serializable, FOptionalString& Platform, FOptionalString& Device, FOptionalString& Source, FOptionalString& Locale, FOptionalSessionLanguageContextDto& Language, FOptionalMapOfString& CustomParams)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Platform = Serializable->Platform;
		Device = Serializable->Device;
		Source = Serializable->Source;
		Locale = Serializable->Locale;
		Language = Serializable->Language;
		CustomParams = Serializable->CustomParams;
	}
		
}

