#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventRewardObtain.h"

#include "EventRewardObtainLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventRewardObtainLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventRewardObtain To JSON String")
	static FString EventRewardObtainToJsonString(const UEventRewardObtain* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventRewardObtain", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventRewardObtain* Make(FString Symbol, int32 Count, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventRewardObtain", meta=(NativeBreakFunc))
	static void Break(const UEventRewardObtain* Serializable, FString& Symbol, int32& Count);
};