
#include "BeamableCore/Public/AutoGen/LeaderboardAddRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardAddRequestBodyLibrary::LeaderboardAddRequestBodyToJsonString(const ULeaderboardAddRequestBody* Serializable, const bool Pretty)
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

ULeaderboardAddRequestBody* ULeaderboardAddRequestBodyLibrary::Make(double Score, int64 Id, FOptionalBool bIncrement, FOptionalDouble MaxScore, FOptionalDouble MinScore, FOptionalMapOfString Stats, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardAddRequestBody>(Outer);
	Serializable->Score = Score;
	Serializable->Id = Id;
	Serializable->bIncrement = bIncrement;
	Serializable->MaxScore = MaxScore;
	Serializable->MinScore = MinScore;
	Serializable->Stats = Stats;
	
	return Serializable;
}

void ULeaderboardAddRequestBodyLibrary::Break(const ULeaderboardAddRequestBody* Serializable, double& Score, int64& Id, FOptionalBool& bIncrement, FOptionalDouble& MaxScore, FOptionalDouble& MinScore, FOptionalMapOfString& Stats)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Score = Serializable->Score;
		Id = Serializable->Id;
		bIncrement = Serializable->bIncrement;
		MaxScore = Serializable->MaxScore;
		MinScore = Serializable->MinScore;
		Stats = Serializable->Stats;
	}
		
}

