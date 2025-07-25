
#include "BeamableCore/Public/AutoGen/LobbyPlayerLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULobbyPlayerLibrary::LobbyPlayerToJsonString(const ULobbyPlayer* Serializable, const bool Pretty)
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

ULobbyPlayer* ULobbyPlayerLibrary::Make(FOptionalBeamGamerTag PlayerId, FOptionalDateTime Joined, FOptionalArrayOfBeamTag Tags, UObject* Outer)
{
	auto Serializable = NewObject<ULobbyPlayer>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Joined = Joined;
	Serializable->Tags = Tags;
	
	return Serializable;
}

void ULobbyPlayerLibrary::Break(const ULobbyPlayer* Serializable, FOptionalBeamGamerTag& PlayerId, FOptionalDateTime& Joined, FOptionalArrayOfBeamTag& Tags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Joined = Serializable->Joined;
		Tags = Serializable->Tags;
	}
		
}

