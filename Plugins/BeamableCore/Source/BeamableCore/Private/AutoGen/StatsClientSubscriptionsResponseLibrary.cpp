
#include "BeamableCore/Public/AutoGen/StatsClientSubscriptionsResponseLibrary.h"

#include "CoreMinimal.h"


FString UStatsClientSubscriptionsResponseLibrary::StatsClientSubscriptionsResponseToJsonString(const UStatsClientSubscriptionsResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UStatsClientSubscriptionsResponse* UStatsClientSubscriptionsResponseLibrary::Make(TArray<UStatClientSubscriptionData*> Subscriptions, UObject* Outer)
{
	auto Serializable = NewObject<UStatsClientSubscriptionsResponse>(Outer);
	Serializable->Subscriptions = Subscriptions;
	
	return Serializable;
}

void UStatsClientSubscriptionsResponseLibrary::Break(const UStatsClientSubscriptionsResponse* Serializable, TArray<UStatClientSubscriptionData*>& Subscriptions)
{
	Subscriptions = Serializable->Subscriptions;
		
}

