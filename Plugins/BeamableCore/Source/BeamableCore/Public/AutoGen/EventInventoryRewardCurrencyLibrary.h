#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventInventoryRewardCurrency.h"

#include "EventInventoryRewardCurrencyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventInventoryRewardCurrencyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="EventInventoryRewardCurrency To JSON String")
	static FString EventInventoryRewardCurrencyToJsonString(const UEventInventoryRewardCurrency* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make EventInventoryRewardCurrency", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventInventoryRewardCurrency* Make(FString Id, int64 Amount, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break EventInventoryRewardCurrency", meta=(NativeBreakFunc))
	static void Break(const UEventInventoryRewardCurrency* Serializable, FString& Id, int64& Amount);
};