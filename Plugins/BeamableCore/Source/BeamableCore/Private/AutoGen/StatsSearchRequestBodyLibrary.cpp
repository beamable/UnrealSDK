
#include "BeamableCore/Public/AutoGen/StatsSearchRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStatsSearchRequestBodyLibrary::StatsSearchRequestBodyToJsonString(const UStatsSearchRequestBody* Serializable, const bool Pretty)
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

UStatsSearchRequestBody* UStatsSearchRequestBodyLibrary::Make(FString Domain, FString Access, FString ObjectType, TArray<UStatsSearchCriteria*> Criteria, UObject* Outer)
{
	auto Serializable = NewObject<UStatsSearchRequestBody>(Outer);
	Serializable->Domain = Domain;
	Serializable->Access = Access;
	Serializable->ObjectType = ObjectType;
	Serializable->Criteria = Criteria;
	
	return Serializable;
}

void UStatsSearchRequestBodyLibrary::Break(const UStatsSearchRequestBody* Serializable, FString& Domain, FString& Access, FString& ObjectType, TArray<UStatsSearchCriteria*>& Criteria)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Domain = Serializable->Domain;
		Access = Serializable->Access;
		ObjectType = Serializable->ObjectType;
		Criteria = Serializable->Criteria;
	}
		
}

