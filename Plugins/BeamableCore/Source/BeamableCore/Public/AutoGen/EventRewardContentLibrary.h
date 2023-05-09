#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventRewardContent.h"

#include "EventRewardContentLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventRewardContentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventRewardContent To JSON String")
	static FString EventRewardContentToJsonString(const UEventRewardContent* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventRewardContent", meta=(DefaultToSelf="Outer", AdvancedDisplay="Max, Currencies, Items, Obtain, Outer", NativeMakeFunc))
	static UEventRewardContent* Make(double Min, FOptionalDouble Max, FOptionalArrayOfEventInventoryRewardCurrency Currencies, FOptionalArrayOfEventInventoryRewardItem Items, FOptionalArrayOfEventRewardObtain Obtain, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventRewardContent", meta=(NativeBreakFunc))
	static void Break(const UEventRewardContent* Serializable, double& Min, FOptionalDouble& Max, FOptionalArrayOfEventInventoryRewardCurrency& Currencies, FOptionalArrayOfEventInventoryRewardItem& Items, FOptionalArrayOfEventRewardObtain& Obtain);
};