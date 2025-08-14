
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

UStatsSearchResponse* UStatsSearchResponseLibrary::Make(int32 Offset, int32 Limit, TArray<FBeamGamerTag> Ids, FOptionalInt64 Total, UObject* Outer)
{
	auto Serializable = NewObject<UStatsSearchResponse>(Outer);
	Serializable->Offset = Offset;
	Serializable->Limit = Limit;
	Serializable->Ids = Ids;
	Serializable->Total = Total;
	
	return Serializable;
}

void UStatsSearchResponseLibrary::Break(const UStatsSearchResponse* Serializable, int32& Offset, int32& Limit, TArray<FBeamGamerTag>& Ids, FOptionalInt64& Total)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Offset = Serializable->Offset;
		Limit = Serializable->Limit;
		Ids = Serializable->Ids;
		Total = Serializable->Total;
	}
		
}

