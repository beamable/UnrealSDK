
#include "BeamableCore/Public/AutoGen/GetStandingsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetStandingsResponseLibrary::GetStandingsResponseToJsonString(const UGetStandingsResponse* Serializable, const bool Pretty)
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

UGetStandingsResponse* UGetStandingsResponseLibrary::Make(TArray<UTournamentEntry*> Entries, FOptionalTournamentEntry Me, UObject* Outer)
{
	auto Serializable = NewObject<UGetStandingsResponse>(Outer);
	Serializable->Entries = Entries;
	Serializable->Me = Me;
	
	return Serializable;
}

void UGetStandingsResponseLibrary::Break(const UGetStandingsResponse* Serializable, TArray<UTournamentEntry*>& Entries, FOptionalTournamentEntry& Me)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Entries = Serializable->Entries;
		Me = Serializable->Me;
	}
		
}

