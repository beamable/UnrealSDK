
#include "BeamableCore/Public/AutoGen/TournamentClientViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTournamentClientViewLibrary::TournamentClientViewToJsonString(const UTournamentClientView* Serializable, const bool Pretty)
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

UTournamentClientView* UTournamentClientViewLibrary::Make(FString TournamentId, FString StartTimeUtc, int64 SecondsRemaining, int32 Cycle, FString EndTimeUtc, FString ContentId, UObject* Outer)
{
	auto Serializable = NewObject<UTournamentClientView>(Outer);
	Serializable->TournamentId = TournamentId;
	Serializable->StartTimeUtc = StartTimeUtc;
	Serializable->SecondsRemaining = SecondsRemaining;
	Serializable->Cycle = Cycle;
	Serializable->EndTimeUtc = EndTimeUtc;
	Serializable->ContentId = ContentId;
	
	return Serializable;
}

void UTournamentClientViewLibrary::Break(const UTournamentClientView* Serializable, FString& TournamentId, FString& StartTimeUtc, int64& SecondsRemaining, int32& Cycle, FString& EndTimeUtc, FString& ContentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TournamentId = Serializable->TournamentId;
		StartTimeUtc = Serializable->StartTimeUtc;
		SecondsRemaining = Serializable->SecondsRemaining;
		Cycle = Serializable->Cycle;
		EndTimeUtc = Serializable->EndTimeUtc;
		ContentId = Serializable->ContentId;
	}
		
}

