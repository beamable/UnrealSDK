
#include "BeamableCore/Public/AutoGen/EventDateRangesLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventDateRangesLibrary::EventDateRangesToJsonString(const UEventDateRanges* Serializable, const bool Pretty)
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

UEventDateRanges* UEventDateRangesLibrary::Make(FString Name, FString State, FString Id, TArray<UDateRange*> Dates, FOptionalInt64 CreatedAt, UObject* Outer)
{
	auto Serializable = NewObject<UEventDateRanges>(Outer);
	Serializable->Name = Name;
	Serializable->State = State;
	Serializable->Id = Id;
	Serializable->Dates = Dates;
	Serializable->CreatedAt = CreatedAt;
	
	return Serializable;
}

void UEventDateRangesLibrary::Break(const UEventDateRanges* Serializable, FString& Name, FString& State, FString& Id, TArray<UDateRange*>& Dates, FOptionalInt64& CreatedAt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		State = Serializable->State;
		Id = Serializable->Id;
		Dates = Serializable->Dates;
		CreatedAt = Serializable->CreatedAt;
	}
		
}

