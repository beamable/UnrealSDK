
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

UInFlightFailure* UInFlightFailureLibrary::Make(FString Id, FString ServiceObjectId, FString ServiceName, UInFlightMessage* InFlightMessage, FString LastError, FOptionalDateTime Timestamp, UObject* Outer)
{
	auto Serializable = NewObject<UInFlightFailure>(Outer);
	Serializable->Id = Id;
	Serializable->ServiceObjectId = ServiceObjectId;
	Serializable->ServiceName = ServiceName;
	Serializable->InFlightMessage = InFlightMessage;
	Serializable->LastError = LastError;
	Serializable->Timestamp = Timestamp;
	
	return Serializable;
}

void UInFlightFailureLibrary::Break(const UInFlightFailure* Serializable, FString& Id, FString& ServiceObjectId, FString& ServiceName, UInFlightMessage*& InFlightMessage, FString& LastError, FOptionalDateTime& Timestamp)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		ServiceObjectId = Serializable->ServiceObjectId;
		ServiceName = Serializable->ServiceName;
		InFlightMessage = Serializable->InFlightMessage;
		LastError = Serializable->LastError;
		Timestamp = Serializable->Timestamp;
	}
		
}

