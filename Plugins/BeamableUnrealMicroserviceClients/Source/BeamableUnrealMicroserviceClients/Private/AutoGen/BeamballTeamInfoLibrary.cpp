
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballTeamInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamballTeamInfoLibrary::BeamballTeamInfoToJsonString(const UBeamballTeamInfo* Serializable, const bool Pretty)
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

UBeamballTeamInfo* UBeamballTeamInfoLibrary::Make(FString TeamName, TArray<UBeamballPlayerInfo*> Players, UObject* Outer)
{
	auto Serializable = NewObject<UBeamballTeamInfo>(Outer);
	Serializable->TeamName = TeamName;
	Serializable->Players = Players;
	
	return Serializable;
}

void UBeamballTeamInfoLibrary::Break(const UBeamballTeamInfo* Serializable, FString& TeamName, TArray<UBeamballPlayerInfo*>& Players)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TeamName = Serializable->TeamName;
		Players = Serializable->Players;
	}
		
}

