
#include "BeamableCore/Public/AutoGen/AuthV2ChallengeSolutionLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2ChallengeSolutionLibrary::AuthV2ChallengeSolutionToJsonString(const UAuthV2ChallengeSolution* Serializable, const bool Pretty)
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

UAuthV2ChallengeSolution* UAuthV2ChallengeSolutionLibrary::Make(FOptionalString ChallengeToken, FOptionalString Solution, UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2ChallengeSolution>(Outer);
	Serializable->ChallengeToken = ChallengeToken;
	Serializable->Solution = Solution;
	
	return Serializable;
}

void UAuthV2ChallengeSolutionLibrary::Break(const UAuthV2ChallengeSolution* Serializable, FOptionalString& ChallengeToken, FOptionalString& Solution)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ChallengeToken = Serializable->ChallengeToken;
		Solution = Serializable->Solution;
	}
		
}

