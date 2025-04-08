#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RewardCalendarDay.h"

#include "RewardCalendarDayLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URewardCalendarDayLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="RewardCalendarDay To JSON String")
	static FString RewardCalendarDayToJsonString(const URewardCalendarDay* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make RewardCalendarDay", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URewardCalendarDay* Make(TArray<UEntitlementGenerator*> Obtain, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break RewardCalendarDay", meta=(NativeBreakFunc))
	static void Break(const URewardCalendarDay* Serializable, TArray<UEntitlementGenerator*>& Obtain);
};