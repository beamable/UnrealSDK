
#include "BeamableCore/Public/AutoGen/StatsUnsubscribeRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStatsUnsubscribeRequestBodyLibrary::StatsUnsubscribeRequestBodyToJsonString(const UStatsUnsubscribeRequestBody* Serializable, const bool Pretty)
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

UStatsUnsubscribeRequestBody* UStatsUnsubscribeRequestBodyLibrary::Make(FString Service, FOptionalArrayOfString Subscriptions, UObject* Outer)
{
	auto Serializable = NewObject<UStatsUnsubscribeRequestBody>(Outer);
	Serializable->Service = Service;
	Serializable->Subscriptions = Subscriptions;
	
	return Serializable;
}

void UStatsUnsubscribeRequestBodyLibrary::Break(const UStatsUnsubscribeRequestBody* Serializable, FString& Service, FOptionalArrayOfString& Subscriptions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Service = Serializable->Service;
		Subscriptions = Serializable->Subscriptions;
	}
		
}

