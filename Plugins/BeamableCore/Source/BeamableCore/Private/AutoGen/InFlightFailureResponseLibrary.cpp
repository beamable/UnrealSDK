
#include "BeamableCore/Public/AutoGen/InFlightFailureResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInFlightFailureResponseLibrary::InFlightFailureResponseToJsonString(const UInFlightFailureResponse* Serializable, const bool Pretty)
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

UInFlightFailureResponse* UInFlightFailureResponseLibrary::Make(TArray<UInFlightFailure*> Failures, UObject* Outer)
{
	auto Serializable = NewObject<UInFlightFailureResponse>(Outer);
	Serializable->Failures = Failures;
	
	return Serializable;
}

void UInFlightFailureResponseLibrary::Break(const UInFlightFailureResponse* Serializable, TArray<UInFlightFailure*>& Failures)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Failures = Serializable->Failures;
	}
		
}

