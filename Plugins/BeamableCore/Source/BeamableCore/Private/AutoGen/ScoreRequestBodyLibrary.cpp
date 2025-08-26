
#include "BeamableCore/Public/AutoGen/ScoreRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UScoreRequestBodyLibrary::ScoreRequestBodyToJsonString(const UScoreRequestBody* Serializable, const bool Pretty)
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

UScoreRequestBody* UScoreRequestBodyLibrary::Make(FString TournamentId, double Score, int64 PlayerId, FOptionalBool bIncrement, FOptionalString ContentId, FOptionalMapOfString Stats, UObject* Outer)
{
	auto Serializable = NewObject<UScoreRequestBody>(Outer);
	Serializable->TournamentId = TournamentId;
	Serializable->Score = Score;
	Serializable->PlayerId = PlayerId;
	Serializable->bIncrement = bIncrement;
	Serializable->ContentId = ContentId;
	Serializable->Stats = Stats;
	
	return Serializable;
}

void UScoreRequestBodyLibrary::Break(const UScoreRequestBody* Serializable, FString& TournamentId, double& Score, int64& PlayerId, FOptionalBool& bIncrement, FOptionalString& ContentId, FOptionalMapOfString& Stats)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		TournamentId = Serializable->TournamentId;
		Score = Serializable->Score;
		PlayerId = Serializable->PlayerId;
		bIncrement = Serializable->bIncrement;
		ContentId = Serializable->ContentId;
		Stats = Serializable->Stats;
	}
		
}

