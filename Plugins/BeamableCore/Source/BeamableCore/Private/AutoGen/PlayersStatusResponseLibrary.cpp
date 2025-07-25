
#include "BeamableCore/Public/AutoGen/PlayersStatusResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPlayersStatusResponseLibrary::PlayersStatusResponseToJsonString(const UPlayersStatusResponse* Serializable, const bool Pretty)
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

UPlayersStatusResponse* UPlayersStatusResponseLibrary::Make(FOptionalArrayOfOnlineStatus PlayersStatus, UObject* Outer)
{
	auto Serializable = NewObject<UPlayersStatusResponse>(Outer);
	Serializable->PlayersStatus = PlayersStatus;
	
	return Serializable;
}

void UPlayersStatusResponseLibrary::Break(const UPlayersStatusResponse* Serializable, FOptionalArrayOfOnlineStatus& PlayersStatus)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayersStatus = Serializable->PlayersStatus;
	}
		
}

