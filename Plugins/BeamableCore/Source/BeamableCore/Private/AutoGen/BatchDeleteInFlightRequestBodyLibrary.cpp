
#include "BeamableCore/Public/AutoGen/BatchDeleteInFlightRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBatchDeleteInFlightRequestBodyLibrary::BatchDeleteInFlightRequestBodyToJsonString(const UBatchDeleteInFlightRequestBody* Serializable, const bool Pretty)
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

UBatchDeleteInFlightRequestBody* UBatchDeleteInFlightRequestBodyLibrary::Make(TArray<FString> InFlightFailureIds, UObject* Outer)
{
	auto Serializable = NewObject<UBatchDeleteInFlightRequestBody>(Outer);
	Serializable->InFlightFailureIds = InFlightFailureIds;
	
	return Serializable;
}

void UBatchDeleteInFlightRequestBodyLibrary::Break(const UBatchDeleteInFlightRequestBody* Serializable, TArray<FString>& InFlightFailureIds)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		InFlightFailureIds = Serializable->InFlightFailureIds;
	}
		
}

