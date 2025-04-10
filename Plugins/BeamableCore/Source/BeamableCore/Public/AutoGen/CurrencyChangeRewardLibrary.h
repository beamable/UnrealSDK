#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CurrencyChangeReward.h"

#include "CurrencyChangeRewardLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyChangeRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|4 - Json", DisplayName="CurrencyChangeReward To JSON String")
	static FString CurrencyChangeRewardToJsonString(const UCurrencyChangeReward* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|3 - Backend", DisplayName="Make CurrencyChangeReward", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCurrencyChangeReward* Make(FString Symbol, int64 Amount, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|3 - Backend", DisplayName="Break CurrencyChangeReward", meta=(NativeBreakFunc))
	static void Break(const UCurrencyChangeReward* Serializable, FString& Symbol, int64& Amount);
};