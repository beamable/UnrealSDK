#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventRewardState.h"

#include "EventRewardStateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventRewardStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="EventRewardState To JSON String")
	static FString EventRewardStateToJsonString(const UEventRewardState* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make EventRewardState", meta=(DefaultToSelf="Outer", AdvancedDisplay="Max, Currencies, PendingItemRewards, Items, Obtain, PendingCurrencyRewards, PendingEntitlementRewards, Outer", NativeMakeFunc))
	static UEventRewardState* Make(bool bClaimed, bool bEarned, UEventInventoryPendingRewards* PendingInventoryRewards, double Min, FOptionalDouble Max, FOptionalArrayOfEventInventoryRewardCurrency Currencies, FOptionalArrayOfItemCreateRequestBody PendingItemRewards, FOptionalArrayOfEventInventoryRewardItem Items, FOptionalArrayOfEventRewardObtain Obtain, FOptionalMapOfString PendingCurrencyRewards, FOptionalMapOfString PendingEntitlementRewards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break EventRewardState", meta=(NativeBreakFunc))
	static void Break(const UEventRewardState* Serializable, bool& bClaimed, bool& bEarned, UEventInventoryPendingRewards*& PendingInventoryRewards, double& Min, FOptionalDouble& Max, FOptionalArrayOfEventInventoryRewardCurrency& Currencies, FOptionalArrayOfItemCreateRequestBody& PendingItemRewards, FOptionalArrayOfEventInventoryRewardItem& Items, FOptionalArrayOfEventRewardObtain& Obtain, FOptionalMapOfString& PendingCurrencyRewards, FOptionalMapOfString& PendingEntitlementRewards);
};