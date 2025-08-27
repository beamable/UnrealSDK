
#include "BeamableCore/Public/AutoGen/RealmConfigResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmConfigResponseLibrary::RealmConfigResponseToJsonString(const URealmConfigResponse* Serializable, const bool Pretty)
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

URealmConfigResponse* URealmConfigResponseLibrary::Make(TMap<FString, FString> Config, UObject* Outer)
{
	auto Serializable = NewObject<URealmConfigResponse>(Outer);
	Serializable->Config = Config;
	
	return Serializable;
}

void URealmConfigResponseLibrary::Break(const URealmConfigResponse* Serializable, TMap<FString, FString>& Config)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Config = Serializable->Config;
	}
		
}

