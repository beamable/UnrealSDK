
#include "BeamableCore/Public/AutoGen/EventClaimRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UEventClaimRequestBodyLibrary::EventClaimRequestBodyToJsonString(const UEventClaimRequestBody* Serializable, const bool Pretty)
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

UEventClaimRequestBody* UEventClaimRequestBodyLibrary::Make(FString EventId, UObject* Outer)
{
	auto Serializable = NewObject<UEventClaimRequestBody>(Outer);
	Serializable->EventId = EventId;
	
	return Serializable;
}

void UEventClaimRequestBodyLibrary::Break(const UEventClaimRequestBody* Serializable, FString& EventId)
{
	EventId = Serializable->EventId;
		
}

