
#include "BeamableCore/Public/AutoGen/EventPhaseTimeLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventPhaseTimeLibrary::EventPhaseTimeToJsonString(const UEventPhaseTime* Serializable, const bool Pretty)
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

UEventPhaseTime* UEventPhaseTimeLibrary::Make(FString Name, FOptionalInt64 StartTime, FOptionalInt64 EndTime, UObject* Outer)
{
	auto Serializable = NewObject<UEventPhaseTime>(Outer);
	Serializable->Name = Name;
	Serializable->StartTime = StartTime;
	Serializable->EndTime = EndTime;
	
	return Serializable;
}

void UEventPhaseTimeLibrary::Break(const UEventPhaseTime* Serializable, FString& Name, FOptionalInt64& StartTime, FOptionalInt64& EndTime)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		StartTime = Serializable->StartTime;
		EndTime = Serializable->EndTime;
	}
		
}

