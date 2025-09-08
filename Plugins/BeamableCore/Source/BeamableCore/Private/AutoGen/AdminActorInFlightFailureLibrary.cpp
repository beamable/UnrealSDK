
#include "BeamableCore/Public/AutoGen/AdminActorInFlightFailureLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAdminActorInFlightFailureLibrary::AdminActorInFlightFailureToJsonString(const UAdminActorInFlightFailure* Serializable, const bool Pretty)
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

UAdminActorInFlightFailure* UAdminActorInFlightFailureLibrary::Make(FString FailureId, FString ServiceObjectId, FString ServiceName, UAdminActorInFlightMessage* InFlightMessage, FString LastError, FOptionalDateTime Timestamp, UObject* Outer)
{
	auto Serializable = NewObject<UAdminActorInFlightFailure>(Outer);
	Serializable->FailureId = FailureId;
	Serializable->ServiceObjectId = ServiceObjectId;
	Serializable->ServiceName = ServiceName;
	Serializable->InFlightMessage = InFlightMessage;
	Serializable->LastError = LastError;
	Serializable->Timestamp = Timestamp;
	
	return Serializable;
}

void UAdminActorInFlightFailureLibrary::Break(const UAdminActorInFlightFailure* Serializable, FString& FailureId, FString& ServiceObjectId, FString& ServiceName, UAdminActorInFlightMessage*& InFlightMessage, FString& LastError, FOptionalDateTime& Timestamp)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		FailureId = Serializable->FailureId;
		ServiceObjectId = Serializable->ServiceObjectId;
		ServiceName = Serializable->ServiceName;
		InFlightMessage = Serializable->InFlightMessage;
		LastError = Serializable->LastError;
		Timestamp = Serializable->Timestamp;
	}
		
}

