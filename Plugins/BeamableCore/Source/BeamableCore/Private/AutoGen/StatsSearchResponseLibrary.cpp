
#include "BeamableCore/Public/AutoGen/StatsSearchResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStatsSearchResponseLibrary::StatsSearchResponseToJsonString(const UStatsSearchResponse* Serializable, const bool Pretty)
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

UStatsSearchResponse* UStatsSearchResponseLibrary::Make(TArray<FBeamGamerTag> Ids, UObject* Outer)
{
	auto Serializable = NewObject<UStatsSearchResponse>(Outer);
	Serializable->Ids = Ids;
	
	return Serializable;
}

void UStatsSearchResponseLibrary::Break(const UStatsSearchResponse* Serializable, TArray<FBeamGamerTag>& Ids)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Ids = Serializable->Ids;
	}
		
}

