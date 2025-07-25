
#include "BeamableCore/Public/AutoGen/ScheduleLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UScheduleLibrary::ScheduleToJsonString(const USchedule* Serializable, const bool Pretty)
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

USchedule* UScheduleLibrary::Make(FString ActiveFrom, FOptionalString Description, FOptionalString ActiveTo, FOptionalArrayOfString Crons, FOptionalArrayOfScheduleDefinition Definitions, UObject* Outer)
{
	auto Serializable = NewObject<USchedule>(Outer);
	Serializable->ActiveFrom = ActiveFrom;
	Serializable->Description = Description;
	Serializable->ActiveTo = ActiveTo;
	Serializable->Crons = Crons;
	Serializable->Definitions = Definitions;
	
	return Serializable;
}

void UScheduleLibrary::Break(const USchedule* Serializable, FString& ActiveFrom, FOptionalString& Description, FOptionalString& ActiveTo, FOptionalArrayOfString& Crons, FOptionalArrayOfScheduleDefinition& Definitions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ActiveFrom = Serializable->ActiveFrom;
		Description = Serializable->Description;
		ActiveTo = Serializable->ActiveTo;
		Crons = Serializable->Crons;
		Definitions = Serializable->Definitions;
	}
		
}

