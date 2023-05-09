#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventInventoryPendingRewards.h"

#include "EventInventoryPendingRewardsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventInventoryPendingRewardsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventInventoryPendingRewards To JSON String")
	static FString EventInventoryPendingRewardsToJsonString(const UEventInventoryPendingRewards* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventInventoryPendingRewards", meta=(DefaultToSelf="Outer", AdvancedDisplay="Items, Currencies, Outer", NativeMakeFunc))
	static UEventInventoryPendingRewards* Make(bool bEmpty, FOptionalArrayOfItemCreateRequestBody Items, FOptionalMapOfString Currencies, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventInventoryPendingRewards", meta=(NativeBreakFunc))
	static void Break(const UEventInventoryPendingRewards* Serializable, bool& bEmpty, FOptionalArrayOfItemCreateRequestBody& Items, FOptionalMapOfString& Currencies);
};