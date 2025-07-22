
#include "BeamableCore/Public/AutoGen/StatsSearchCriteriaLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStatsSearchCriteriaLibrary::StatsSearchCriteriaToJsonString(const UStatsSearchCriteria* Serializable, const bool Pretty)
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

UStatsSearchCriteria* UStatsSearchCriteriaLibrary::Make(FString Stat, FString Rel, FOptionalString Value, UObject* Outer)
{
	auto Serializable = NewObject<UStatsSearchCriteria>(Outer);
	Serializable->Stat = Stat;
	Serializable->Rel = Rel;
	Serializable->Value = Value;
	
	return Serializable;
}

void UStatsSearchCriteriaLibrary::Break(const UStatsSearchCriteria* Serializable, FString& Stat, FString& Rel, FOptionalString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Stat = Serializable->Stat;
		Rel = Serializable->Rel;
		Value = Serializable->Value;
	}
		
}

