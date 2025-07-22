
#include "BeamableCore/Public/AutoGen/LeaderboardCohortLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULeaderboardCohortLibrary::LeaderboardCohortToJsonString(const ULeaderboardCohort* Serializable, const bool Pretty)
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

ULeaderboardCohort* ULeaderboardCohortLibrary::Make(FString Id, TArray<UPlayerStatRequirement*> StatRequirements, FOptionalString Description, UObject* Outer)
{
	auto Serializable = NewObject<ULeaderboardCohort>(Outer);
	Serializable->Id = Id;
	Serializable->StatRequirements = StatRequirements;
	Serializable->Description = Description;
	
	return Serializable;
}

void ULeaderboardCohortLibrary::Break(const ULeaderboardCohort* Serializable, FString& Id, TArray<UPlayerStatRequirement*>& StatRequirements, FOptionalString& Description)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		StatRequirements = Serializable->StatRequirements;
		Description = Serializable->Description;
	}
		
}

