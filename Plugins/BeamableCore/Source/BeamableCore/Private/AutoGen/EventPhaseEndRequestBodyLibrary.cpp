
#include "BeamableCore/Public/AutoGen/EventPhaseEndRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UEventPhaseEndRequestBodyLibrary::EventPhaseEndRequestBodyToJsonString(const UEventPhaseEndRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UEventPhaseEndRequestBody* UEventPhaseEndRequestBodyLibrary::Make(FOptionalString Time, UObject* Outer)
{
	auto Serializable = NewObject<UEventPhaseEndRequestBody>(Outer);
	Serializable->Time = Time;
	
	return Serializable;
}

void UEventPhaseEndRequestBodyLibrary::Break(const UEventPhaseEndRequestBody* Serializable, FOptionalString& Time)
{
	Time = Serializable->Time;
		
}

