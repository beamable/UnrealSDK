
#include "BeamableCore/Public/AutoGen/StatSubscriptionNotificationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStatSubscriptionNotificationLibrary::StatSubscriptionNotificationToJsonString(const UStatSubscriptionNotification* Serializable, const bool Pretty)
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

UStatSubscriptionNotification* UStatSubscriptionNotificationLibrary::Make(TMap<FString, FString> StatsBefore, TMap<FString, FString> StatsAfter, UObject* Outer)
{
	auto Serializable = NewObject<UStatSubscriptionNotification>(Outer);
	Serializable->StatsBefore = StatsBefore;
	Serializable->StatsAfter = StatsAfter;
	
	return Serializable;
}

void UStatSubscriptionNotificationLibrary::Break(const UStatSubscriptionNotification* Serializable, TMap<FString, FString>& StatsBefore, TMap<FString, FString>& StatsAfter)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		StatsBefore = Serializable->StatsBefore;
		StatsAfter = Serializable->StatsAfter;
	}
		
}

