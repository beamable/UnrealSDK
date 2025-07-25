
#include "BeamableCore/Public/AutoGen/InFlightFailureLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UInFlightFailureLibrary::InFlightFailureToJsonString(const UInFlightFailure* Serializable, const bool Pretty)
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

UInFlightFailure* UInFlightFailureLibrary::Make(FString ServiceObjectId, int64 Timestamp, FString ServiceName, UInFlightMessage* InFlightMessage, FString LastError, FString Id, UObject* Outer)
{
	auto Serializable = NewObject<UInFlightFailure>(Outer);
	Serializable->ServiceObjectId = ServiceObjectId;
	Serializable->Timestamp = Timestamp;
	Serializable->ServiceName = ServiceName;
	Serializable->InFlightMessage = InFlightMessage;
	Serializable->LastError = LastError;
	Serializable->Id = Id;
	
	return Serializable;
}

void UInFlightFailureLibrary::Break(const UInFlightFailure* Serializable, FString& ServiceObjectId, int64& Timestamp, FString& ServiceName, UInFlightMessage*& InFlightMessage, FString& LastError, FString& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ServiceObjectId = Serializable->ServiceObjectId;
		Timestamp = Serializable->Timestamp;
		ServiceName = Serializable->ServiceName;
		InFlightMessage = Serializable->InFlightMessage;
		LastError = Serializable->LastError;
		Id = Serializable->Id;
	}
		
}

