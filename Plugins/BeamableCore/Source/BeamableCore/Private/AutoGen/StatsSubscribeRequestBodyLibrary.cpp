
#include "BeamableCore/Public/AutoGen/StatsSubscribeRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStatsSubscribeRequestBodyLibrary::StatsSubscribeRequestBodyToJsonString(const UStatsSubscribeRequestBody* Serializable, const bool Pretty)
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

UStatsSubscribeRequestBody* UStatsSubscribeRequestBodyLibrary::Make(FString Service, TArray<FString> Subscriptions, UObject* Outer)
{
	auto Serializable = NewObject<UStatsSubscribeRequestBody>(Outer);
	Serializable->Service = Service;
	Serializable->Subscriptions = Subscriptions;
	
	return Serializable;
}

void UStatsSubscribeRequestBodyLibrary::Break(const UStatsSubscribeRequestBody* Serializable, FString& Service, TArray<FString>& Subscriptions)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Service = Serializable->Service;
		Subscriptions = Serializable->Subscriptions;
	}
		
}

