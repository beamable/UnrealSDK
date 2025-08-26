
#include "BeamableCore/Public/AutoGen/EventPhaseEndRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventPhaseEndRequestBodyLibrary::EventPhaseEndRequestBodyToJsonString(const UEventPhaseEndRequestBody* Serializable, const bool Pretty)
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

UEventPhaseEndRequestBody* UEventPhaseEndRequestBodyLibrary::Make(FOptionalString Time, UObject* Outer)
{
	auto Serializable = NewObject<UEventPhaseEndRequestBody>(Outer);
	Serializable->Time = Time;
	
	return Serializable;
}

void UEventPhaseEndRequestBodyLibrary::Break(const UEventPhaseEndRequestBody* Serializable, FOptionalString& Time)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Time = Serializable->Time;
	}
		
}

