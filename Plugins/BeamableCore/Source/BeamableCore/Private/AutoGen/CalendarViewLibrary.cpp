
#include "BeamableCore/Public/AutoGen/CalendarViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCalendarViewLibrary::CalendarViewToJsonString(const UCalendarView* Serializable, const bool Pretty)
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

UCalendarView* UCalendarViewLibrary::Make(int32 NextIndex, int64 NextClaimSeconds, FString Id, int64 RemainingSeconds, TArray<URewardCalendarDay*> Days, UObject* Outer)
{
	auto Serializable = NewObject<UCalendarView>(Outer);
	Serializable->NextIndex = NextIndex;
	Serializable->NextClaimSeconds = NextClaimSeconds;
	Serializable->Id = Id;
	Serializable->RemainingSeconds = RemainingSeconds;
	Serializable->Days = Days;
	
	return Serializable;
}

void UCalendarViewLibrary::Break(const UCalendarView* Serializable, int32& NextIndex, int64& NextClaimSeconds, FString& Id, int64& RemainingSeconds, TArray<URewardCalendarDay*>& Days)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		NextIndex = Serializable->NextIndex;
		NextClaimSeconds = Serializable->NextClaimSeconds;
		Id = Serializable->Id;
		RemainingSeconds = Serializable->RemainingSeconds;
		Days = Serializable->Days;
	}
		
}

