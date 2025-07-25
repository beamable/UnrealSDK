
#include "BeamableCore/Public/AutoGen/ChallengeSolutionLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UChallengeSolutionLibrary::ChallengeSolutionToJsonString(const UChallengeSolution* Serializable, const bool Pretty)
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

UChallengeSolution* UChallengeSolutionLibrary::Make(FString ChallengeToken, FString Solution, UObject* Outer)
{
	auto Serializable = NewObject<UChallengeSolution>(Outer);
	Serializable->ChallengeToken = ChallengeToken;
	Serializable->Solution = Solution;
	
	return Serializable;
}

void UChallengeSolutionLibrary::Break(const UChallengeSolution* Serializable, FString& ChallengeToken, FString& Solution)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ChallengeToken = Serializable->ChallengeToken;
		Solution = Serializable->Solution;
	}
		
}

