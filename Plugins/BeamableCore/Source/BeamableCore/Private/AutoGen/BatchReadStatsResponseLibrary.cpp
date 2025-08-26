
#include "BeamableCore/Public/AutoGen/BatchReadStatsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBatchReadStatsResponseLibrary::BatchReadStatsResponseToJsonString(const UBatchReadStatsResponse* Serializable, const bool Pretty)
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

UBatchReadStatsResponse* UBatchReadStatsResponseLibrary::Make(TArray<UNetworkSerializable*> Results, UObject* Outer)
{
	auto Serializable = NewObject<UBatchReadStatsResponse>(Outer);
	Serializable->Results = Results;
	
	return Serializable;
}

void UBatchReadStatsResponseLibrary::Break(const UBatchReadStatsResponse* Serializable, TArray<UNetworkSerializable*>& Results)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Results = Serializable->Results;
	}
		
}

