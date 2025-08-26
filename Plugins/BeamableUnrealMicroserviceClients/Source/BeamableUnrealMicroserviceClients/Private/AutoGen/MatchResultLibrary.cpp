
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MatchResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMatchResultLibrary::MatchResultToJsonString(const UMatchResult* Serializable, const bool Pretty)
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

UMatchResult* UMatchResultLibrary::Make(TMap<FString, UPerPlayerMatchResult*> PerPlayerMatchResults, UObject* Outer)
{
	auto Serializable = NewObject<UMatchResult>(Outer);
	Serializable->PerPlayerMatchResults = PerPlayerMatchResults;
	
	return Serializable;
}

void UMatchResultLibrary::Break(const UMatchResult* Serializable, TMap<FString, UPerPlayerMatchResult*>& PerPlayerMatchResults)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PerPlayerMatchResults = Serializable->PerPlayerMatchResults;
	}
		
}

