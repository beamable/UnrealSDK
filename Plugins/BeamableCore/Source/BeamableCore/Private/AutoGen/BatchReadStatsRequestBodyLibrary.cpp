
#include "BeamableCore/Public/AutoGen/BatchReadStatsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBatchReadStatsRequestBodyLibrary::BatchReadStatsRequestBodyToJsonString(const UBatchReadStatsRequestBody* Serializable, const bool Pretty)
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

UBatchReadStatsRequestBody* UBatchReadStatsRequestBodyLibrary::Make(FBeamStatsType ObjectIds, FOptionalString Stats, FOptionalString Format, UObject* Outer)
{
	auto Serializable = NewObject<UBatchReadStatsRequestBody>(Outer);
	Serializable->ObjectIds = ObjectIds;
	Serializable->Stats = Stats;
	Serializable->Format = Format;
	
	return Serializable;
}

void UBatchReadStatsRequestBodyLibrary::Break(const UBatchReadStatsRequestBody* Serializable, FBeamStatsType& ObjectIds, FOptionalString& Stats, FOptionalString& Format)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ObjectIds = Serializable->ObjectIds;
		Stats = Serializable->Stats;
		Format = Serializable->Format;
	}
		
}

