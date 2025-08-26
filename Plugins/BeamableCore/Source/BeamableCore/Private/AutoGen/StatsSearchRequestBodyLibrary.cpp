
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

UStatsSearchRequestBody* UStatsSearchRequestBodyLibrary::Make(FString Domain, FString ObjectType, FString Access, TArray<UStatsSearchCriteria*> Criteria, FOptionalInt32 Offset, FOptionalInt32 Limit, UObject* Outer)
{
	auto Serializable = NewObject<UStatsSearchRequestBody>(Outer);
	Serializable->Domain = Domain;
	Serializable->ObjectType = ObjectType;
	Serializable->Access = Access;
	Serializable->Criteria = Criteria;
	Serializable->Offset = Offset;
	Serializable->Limit = Limit;
	
	return Serializable;
}

void UStatsSearchRequestBodyLibrary::Break(const UStatsSearchRequestBody* Serializable, FString& Domain, FString& ObjectType, FString& Access, TArray<UStatsSearchCriteria*>& Criteria, FOptionalInt32& Offset, FOptionalInt32& Limit)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Domain = Serializable->Domain;
		ObjectType = Serializable->ObjectType;
		Access = Serializable->Access;
		Criteria = Serializable->Criteria;
		Offset = Serializable->Offset;
		Limit = Serializable->Limit;
	}
		
}

