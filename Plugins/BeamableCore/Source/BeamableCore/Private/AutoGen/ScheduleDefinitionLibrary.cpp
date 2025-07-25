
#include "BeamableCore/Public/AutoGen/ScheduleDefinitionLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UScheduleDefinitionLibrary::ScheduleDefinitionToJsonString(const UScheduleDefinition* Serializable, const bool Pretty)
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

UScheduleDefinition* UScheduleDefinitionLibrary::Make(TArray<FString> DayOfWeek, TArray<FString> Minute, TArray<FString> DayOfMonth, TArray<FString> Year, TArray<FString> Hour, TArray<FString> Second, TArray<FString> Month, UObject* Outer)
{
	auto Serializable = NewObject<UScheduleDefinition>(Outer);
	Serializable->DayOfWeek = DayOfWeek;
	Serializable->Minute = Minute;
	Serializable->DayOfMonth = DayOfMonth;
	Serializable->Year = Year;
	Serializable->Hour = Hour;
	Serializable->Second = Second;
	Serializable->Month = Month;
	
	return Serializable;
}

void UScheduleDefinitionLibrary::Break(const UScheduleDefinition* Serializable, TArray<FString>& DayOfWeek, TArray<FString>& Minute, TArray<FString>& DayOfMonth, TArray<FString>& Year, TArray<FString>& Hour, TArray<FString>& Second, TArray<FString>& Month)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		DayOfWeek = Serializable->DayOfWeek;
		Minute = Serializable->Minute;
		DayOfMonth = Serializable->DayOfMonth;
		Year = Serializable->Year;
		Hour = Serializable->Hour;
		Second = Serializable->Second;
		Month = Serializable->Month;
	}
		
}

