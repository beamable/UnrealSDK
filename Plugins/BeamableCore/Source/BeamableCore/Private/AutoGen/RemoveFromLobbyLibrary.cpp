
#include "BeamableCore/Public/AutoGen/RemoveFromLobbyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URemoveFromLobbyLibrary::RemoveFromLobbyToJsonString(const URemoveFromLobby* Serializable, const bool Pretty)
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

URemoveFromLobby* URemoveFromLobbyLibrary::Make(FOptionalBeamGamerTag PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<URemoveFromLobby>(Outer);
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void URemoveFromLobbyLibrary::Break(const URemoveFromLobby* Serializable, FOptionalBeamGamerTag& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
	}
		
}

