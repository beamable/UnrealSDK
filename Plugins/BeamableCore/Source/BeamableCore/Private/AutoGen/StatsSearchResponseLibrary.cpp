
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

UStatsSearchResponse* UStatsSearchResponseLibrary::Make(TArray<FBeamGamerTag> Ids, FOptionalInt32 Offset, FOptionalInt32 Limit, FOptionalInt64 Total, UObject* Outer)
{
	auto Serializable = NewObject<UStatsSearchResponse>(Outer);
	Serializable->Ids = Ids;
	Serializable->Offset = Offset;
	Serializable->Limit = Limit;
	Serializable->Total = Total;
	
	return Serializable;
}

void UStatsSearchResponseLibrary::Break(const UStatsSearchResponse* Serializable, TArray<FBeamGamerTag>& Ids, FOptionalInt32& Offset, FOptionalInt32& Limit, FOptionalInt64& Total)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Ids = Serializable->Ids;
		Offset = Serializable->Offset;
		Limit = Serializable->Limit;
		Total = Serializable->Total;
	}
		
}

