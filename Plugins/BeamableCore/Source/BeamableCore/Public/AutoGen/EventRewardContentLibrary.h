#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventRewardContent.h"

#include "EventRewardContentLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventRewardContentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventRewardContent To JSON String")
	static FString EventRewardContentToJsonString(const UEventRewardContent* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventRewardContent", meta=(DefaultToSelf="Outer", AdvancedDisplay="Max, Currencies, Items, Obtain, Outer", NativeMakeFunc))
	static UEventRewardContent* Make(double Min, FOptionalDouble Max, FOptionalArrayOfEventInventoryRewardCurrency Currencies, FOptionalArrayOfEventInventoryRewardItem Items, FOptionalArrayOfEventRewardObtain Obtain, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventRewardContent", meta=(NativeBreakFunc))
	static void Break(const UEventRewardContent* Serializable, double& Min, FOptionalDouble& Max, FOptionalArrayOfEventInventoryRewardCurrency& Currencies, FOptionalArrayOfEventInventoryRewardItem& Items, FOptionalArrayOfEventRewardObtain& Obtain);
};