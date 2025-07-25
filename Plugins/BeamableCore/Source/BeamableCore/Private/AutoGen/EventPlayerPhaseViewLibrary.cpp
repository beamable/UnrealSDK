
#include "BeamableCore/Public/AutoGen/EventPlayerPhaseViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventPlayerPhaseViewLibrary::EventPlayerPhaseViewToJsonString(const UEventPlayerPhaseView* Serializable, const bool Pretty)
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

UEventPlayerPhaseView* UEventPlayerPhaseViewLibrary::Make(FString Name, int64 DurationSeconds, TArray<UEventRule*> Rules, UObject* Outer)
{
	auto Serializable = NewObject<UEventPlayerPhaseView>(Outer);
	Serializable->Name = Name;
	Serializable->DurationSeconds = DurationSeconds;
	Serializable->Rules = Rules;
	
	return Serializable;
}

void UEventPlayerPhaseViewLibrary::Break(const UEventPlayerPhaseView* Serializable, FString& Name, int64& DurationSeconds, TArray<UEventRule*>& Rules)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		DurationSeconds = Serializable->DurationSeconds;
		Rules = Serializable->Rules;
	}
		
}

