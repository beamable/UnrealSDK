
#include "BeamableCore/Public/AutoGen/RewardCalendarDayLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URewardCalendarDayLibrary::RewardCalendarDayToJsonString(const URewardCalendarDay* Serializable, const bool Pretty)
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

URewardCalendarDay* URewardCalendarDayLibrary::Make(TArray<UEntitlementGenerator*> Obtain, UObject* Outer)
{
	auto Serializable = NewObject<URewardCalendarDay>(Outer);
	Serializable->Obtain = Obtain;
	
	return Serializable;
}

void URewardCalendarDayLibrary::Break(const URewardCalendarDay* Serializable, TArray<UEntitlementGenerator*>& Obtain)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Obtain = Serializable->Obtain;
	}
		
}

