
#include "BeamableCore/Public/AutoGen/TournamentQueryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTournamentQueryResponseLibrary::TournamentQueryResponseToJsonString(const UTournamentQueryResponse* Serializable, const bool Pretty)
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

UTournamentQueryResponse* UTournamentQueryResponseLibrary::Make(TArray<UTournamentClientView*> Tournaments, UObject* Outer)
{
	auto Serializable = NewObject<UTournamentQueryResponse>(Outer);
	Serializable->Tournaments = Tournaments;
	
	return Serializable;
}

void UTournamentQueryResponseLibrary::Break(const UTournamentQueryResponse* Serializable, TArray<UTournamentClientView*>& Tournaments)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Tournaments = Serializable->Tournaments;
	}
		
}

