
#include "BeamableCore/Public/AutoGen/StatsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStatsResponseLibrary::StatsResponseToJsonString(const UStatsResponse* Serializable, const bool Pretty)
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

UStatsResponse* UStatsResponseLibrary::Make(FBeamGamerTag Id, TMap<FString, FString> Stats, UObject* Outer)
{
	auto Serializable = NewObject<UStatsResponse>(Outer);
	Serializable->Id = Id;
	Serializable->Stats = Stats;
	
	return Serializable;
}

void UStatsResponseLibrary::Break(const UStatsResponse* Serializable, FBeamGamerTag& Id, TMap<FString, FString>& Stats)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Stats = Serializable->Stats;
	}
		
}

