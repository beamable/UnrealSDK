
#include "BeamableCore/Public/AutoGen/EventPhaseRuntimeLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventPhaseRuntimeLibrary::EventPhaseRuntimeToJsonString(const UEventPhaseRuntime* Serializable, const bool Pretty)
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

UEventPhaseRuntime* UEventPhaseRuntimeLibrary::Make(FString Name, int64 StartTime, int64 EndTime, TArray<UEventRule*> Rules, UObject* Outer)
{
	auto Serializable = NewObject<UEventPhaseRuntime>(Outer);
	Serializable->Name = Name;
	Serializable->StartTime = StartTime;
	Serializable->EndTime = EndTime;
	Serializable->Rules = Rules;
	
	return Serializable;
}

void UEventPhaseRuntimeLibrary::Break(const UEventPhaseRuntime* Serializable, FString& Name, int64& StartTime, int64& EndTime, TArray<UEventRule*>& Rules)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		StartTime = Serializable->StartTime;
		EndTime = Serializable->EndTime;
		Rules = Serializable->Rules;
	}
		
}

