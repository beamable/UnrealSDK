
#include "BeamableCore/Public/AutoGen/RealmConfigSaveRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmConfigSaveRequestBodyLibrary::RealmConfigSaveRequestBodyToJsonString(const URealmConfigSaveRequestBody* Serializable, const bool Pretty)
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

URealmConfigSaveRequestBody* URealmConfigSaveRequestBodyLibrary::Make(TMap<FString, FString> Config, UObject* Outer)
{
	auto Serializable = NewObject<URealmConfigSaveRequestBody>(Outer);
	Serializable->Config = Config;
	
	return Serializable;
}

void URealmConfigSaveRequestBodyLibrary::Break(const URealmConfigSaveRequestBody* Serializable, TMap<FString, FString>& Config)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Config = Serializable->Config;
	}
		
}

