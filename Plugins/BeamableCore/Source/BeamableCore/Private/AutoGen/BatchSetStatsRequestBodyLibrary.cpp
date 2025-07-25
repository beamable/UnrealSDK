
#include "BeamableCore/Public/AutoGen/BatchSetStatsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBatchSetStatsRequestBodyLibrary::BatchSetStatsRequestBodyToJsonString(const UBatchSetStatsRequestBody* Serializable, const bool Pretty)
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

UBatchSetStatsRequestBody* UBatchSetStatsRequestBodyLibrary::Make(TArray<UStatUpdateRequestBody*> Updates, UObject* Outer)
{
	auto Serializable = NewObject<UBatchSetStatsRequestBody>(Outer);
	Serializable->Updates = Updates;
	
	return Serializable;
}

void UBatchSetStatsRequestBodyLibrary::Break(const UBatchSetStatsRequestBody* Serializable, TArray<UStatUpdateRequestBody*>& Updates)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Updates = Serializable->Updates;
	}
		
}

