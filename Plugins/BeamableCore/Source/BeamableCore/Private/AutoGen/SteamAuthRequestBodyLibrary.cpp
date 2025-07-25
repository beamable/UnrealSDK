
#include "BeamableCore/Public/AutoGen/SteamAuthRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USteamAuthRequestBodyLibrary::SteamAuthRequestBodyToJsonString(const USteamAuthRequestBody* Serializable, const bool Pretty)
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

USteamAuthRequestBody* USteamAuthRequestBodyLibrary::Make(FString Ticket, UObject* Outer)
{
	auto Serializable = NewObject<USteamAuthRequestBody>(Outer);
	Serializable->Ticket = Ticket;
	
	return Serializable;
}

void USteamAuthRequestBodyLibrary::Break(const USteamAuthRequestBody* Serializable, FString& Ticket)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Ticket = Serializable->Ticket;
	}
		
}

