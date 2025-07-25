
#include "BeamableCore/Public/AutoGen/EventPhaseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventPhaseLibrary::EventPhaseToJsonString(const UEventPhase* Serializable, const bool Pretty)
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

UEventPhase* UEventPhaseLibrary::Make(FString Name, int32 DurationMinutes, int64 DurationMillis, int64 DurationSeconds, FOptionalArrayOfEventRule Rules, UObject* Outer)
{
	auto Serializable = NewObject<UEventPhase>(Outer);
	Serializable->Name = Name;
	Serializable->DurationMinutes = DurationMinutes;
	Serializable->DurationMillis = DurationMillis;
	Serializable->DurationSeconds = DurationSeconds;
	Serializable->Rules = Rules;
	
	return Serializable;
}

void UEventPhaseLibrary::Break(const UEventPhase* Serializable, FString& Name, int32& DurationMinutes, int64& DurationMillis, int64& DurationSeconds, FOptionalArrayOfEventRule& Rules)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		DurationMinutes = Serializable->DurationMinutes;
		DurationMillis = Serializable->DurationMillis;
		DurationSeconds = Serializable->DurationSeconds;
		Rules = Serializable->Rules;
	}
		
}

