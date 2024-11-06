
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordWhitelistedInfoLibrary.h"

#include "CoreMinimal.h"


FString UDiscordWhitelistedInfoLibrary::DiscordWhitelistedInfoToJsonString(const UDiscordWhitelistedInfo* Serializable, const bool Pretty)
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

UDiscordWhitelistedInfo* UDiscordWhitelistedInfoLibrary::Make(bool bMatchmakingDiscordWhitelisted, UObject* Outer)
{
	auto Serializable = NewObject<UDiscordWhitelistedInfo>(Outer);
	Serializable->bMatchmakingDiscordWhitelisted = bMatchmakingDiscordWhitelisted;
	
	return Serializable;
}

void UDiscordWhitelistedInfoLibrary::Break(const UDiscordWhitelistedInfo* Serializable, bool& bMatchmakingDiscordWhitelisted)
{
	bMatchmakingDiscordWhitelisted = Serializable->bMatchmakingDiscordWhitelisted;
		
}

