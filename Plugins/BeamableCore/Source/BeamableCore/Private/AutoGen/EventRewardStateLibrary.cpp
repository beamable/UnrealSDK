
#include "BeamableCore/Public/AutoGen/EventRewardStateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventRewardStateLibrary::EventRewardStateToJsonString(const UEventRewardState* Serializable, const bool Pretty)
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

UEventRewardState* UEventRewardStateLibrary::Make(bool bClaimed, bool bEarned, UEventInventoryPendingRewards* PendingInventoryRewards, double Min, FOptionalDouble Max, FOptionalArrayOfEventInventoryRewardCurrency Currencies, FOptionalArrayOfItemCreateRequestBody PendingItemRewards, FOptionalArrayOfEventInventoryRewardItem Items, FOptionalArrayOfEventRewardObtain Obtain, FOptionalMapOfString PendingCurrencyRewards, FOptionalMapOfString PendingEntitlementRewards, UObject* Outer)
{
	auto Serializable = NewObject<UEventRewardState>(Outer);
	Serializable->bClaimed = bClaimed;
	Serializable->bEarned = bEarned;
	Serializable->PendingInventoryRewards = PendingInventoryRewards;
	Serializable->Min = Min;
	Serializable->Max = Max;
	Serializable->Currencies = Currencies;
	Serializable->PendingItemRewards = PendingItemRewards;
	Serializable->Items = Items;
	Serializable->Obtain = Obtain;
	Serializable->PendingCurrencyRewards = PendingCurrencyRewards;
	Serializable->PendingEntitlementRewards = PendingEntitlementRewards;
	
	return Serializable;
}

void UEventRewardStateLibrary::Break(const UEventRewardState* Serializable, bool& bClaimed, bool& bEarned, UEventInventoryPendingRewards*& PendingInventoryRewards, double& Min, FOptionalDouble& Max, FOptionalArrayOfEventInventoryRewardCurrency& Currencies, FOptionalArrayOfItemCreateRequestBody& PendingItemRewards, FOptionalArrayOfEventInventoryRewardItem& Items, FOptionalArrayOfEventRewardObtain& Obtain, FOptionalMapOfString& PendingCurrencyRewards, FOptionalMapOfString& PendingEntitlementRewards)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bClaimed = Serializable->bClaimed;
		bEarned = Serializable->bEarned;
		PendingInventoryRewards = Serializable->PendingInventoryRewards;
		Min = Serializable->Min;
		Max = Serializable->Max;
		Currencies = Serializable->Currencies;
		PendingItemRewards = Serializable->PendingItemRewards;
		Items = Serializable->Items;
		Obtain = Serializable->Obtain;
		PendingCurrencyRewards = Serializable->PendingCurrencyRewards;
		PendingEntitlementRewards = Serializable->PendingEntitlementRewards;
	}
		
}

