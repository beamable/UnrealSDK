
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordSampleMsUpdateFromDiscordResponseLibrary.h"

#include "CoreMinimal.h"


FString UDiscordSampleMsUpdateFromDiscordResponseLibrary::DiscordSampleMsUpdateFromDiscordResponseToJsonString(const UDiscordSampleMsUpdateFromDiscordResponse* Serializable, const bool Pretty)
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

UDiscordSampleMsUpdateFromDiscordResponse* UDiscordSampleMsUpdateFromDiscordResponseLibrary::Make(bool bValue, UObject* Outer)
{
	auto Serializable = NewObject<UDiscordSampleMsUpdateFromDiscordResponse>(Outer);
	Serializable->bValue = bValue;
	
	return Serializable;
}

void UDiscordSampleMsUpdateFromDiscordResponseLibrary::Break(const UDiscordSampleMsUpdateFromDiscordResponse* Serializable, bool& bValue)
{
	bValue = Serializable->bValue;
		
}

