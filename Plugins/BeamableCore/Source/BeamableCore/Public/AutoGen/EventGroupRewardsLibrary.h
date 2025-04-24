#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventGroupRewards.h"

#include "EventGroupRewardsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventGroupRewardsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventGroupRewards To JSON String")
	static FString EventGroupRewardsToJsonString(const UEventGroupRewards* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventGroupRewards", meta=(DefaultToSelf="Outer", AdvancedDisplay="ScoreRewards, Outer", NativeMakeFunc))
	static UEventGroupRewards* Make(FOptionalArrayOfEventRewardContent ScoreRewards, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventGroupRewards", meta=(NativeBreakFunc))
	static void Break(const UEventGroupRewards* Serializable, FOptionalArrayOfEventRewardContent& ScoreRewards);
};