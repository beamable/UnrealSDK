
#include "BeamableCore/Public/AutoGen/RealmsBasicInFlightFailureLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicInFlightFailureLibrary::RealmsBasicInFlightFailureToJsonString(const URealmsBasicInFlightFailure* Serializable, const bool Pretty)
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

URealmsBasicInFlightFailure* URealmsBasicInFlightFailureLibrary::Make(FString ServiceObjectId, int64 Timestamp, FString ServiceName, URealmsBasicInFlightMessage* InFlightMessage, FString LastError, FString Id, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicInFlightFailure>(Outer);
	Serializable->ServiceObjectId = ServiceObjectId;
	Serializable->Timestamp = Timestamp;
	Serializable->ServiceName = ServiceName;
	Serializable->InFlightMessage = InFlightMessage;
	Serializable->LastError = LastError;
	Serializable->Id = Id;
	
	return Serializable;
}

void URealmsBasicInFlightFailureLibrary::Break(const URealmsBasicInFlightFailure* Serializable, FString& ServiceObjectId, int64& Timestamp, FString& ServiceName, URealmsBasicInFlightMessage*& InFlightMessage, FString& LastError, FString& Id)
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

