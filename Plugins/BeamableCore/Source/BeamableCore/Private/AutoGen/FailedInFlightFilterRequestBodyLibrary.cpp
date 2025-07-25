
#include "BeamableCore/Public/AutoGen/FailedInFlightFilterRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UFailedInFlightFilterRequestBodyLibrary::FailedInFlightFilterRequestBodyToJsonString(const UFailedInFlightFilterRequestBody* Serializable, const bool Pretty)
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

UFailedInFlightFilterRequestBody* UFailedInFlightFilterRequestBodyLibrary::Make(FString ServiceName, FOptionalString ServiceObjectId, UObject* Outer)
{
	auto Serializable = NewObject<UFailedInFlightFilterRequestBody>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->ServiceObjectId = ServiceObjectId;
	
	return Serializable;
}

void UFailedInFlightFilterRequestBodyLibrary::Break(const UFailedInFlightFilterRequestBody* Serializable, FString& ServiceName, FOptionalString& ServiceObjectId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ServiceName = Serializable->ServiceName;
		ServiceObjectId = Serializable->ServiceObjectId;
	}
		
}

