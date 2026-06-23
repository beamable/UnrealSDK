
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliveryOrderInfoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeliveryOrderInfoLibrary::DeliveryOrderInfoToJsonString(const UDeliveryOrderInfo* Serializable, const bool Pretty)
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

UDeliveryOrderInfo* UDeliveryOrderInfoLibrary::Make(FString OrderId, FString DisplayName, FString RequiredItemContentId, FString RewardCurrencyId, int32 RewardAmount, TArray<UDeliveryRequirement*> Requirements, UObject* Outer)
{
	auto Serializable = NewObject<UDeliveryOrderInfo>(Outer);
	Serializable->OrderId = OrderId;
	Serializable->DisplayName = DisplayName;
	Serializable->RequiredItemContentId = RequiredItemContentId;
	Serializable->RewardCurrencyId = RewardCurrencyId;
	Serializable->RewardAmount = RewardAmount;
	Serializable->Requirements = Requirements;
	
	return Serializable;
}

void UDeliveryOrderInfoLibrary::Break(const UDeliveryOrderInfo* Serializable, FString& OrderId, FString& DisplayName, FString& RequiredItemContentId, FString& RewardCurrencyId, int32& RewardAmount, TArray<UDeliveryRequirement*>& Requirements)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		OrderId = Serializable->OrderId;
		DisplayName = Serializable->DisplayName;
		RequiredItemContentId = Serializable->RequiredItemContentId;
		RewardCurrencyId = Serializable->RewardCurrencyId;
		RewardAmount = Serializable->RewardAmount;
		Requirements = Serializable->Requirements;
	}
		
}

