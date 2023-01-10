
#include "AutoGen/StatsSearchResponseLibrary.h"

#include "CoreMinimal.h"


FString UStatsSearchResponseLibrary::StatsSearchResponseToJsonString(const UStatsSearchResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
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
	Ids = Serializable->Ids;
		
}
