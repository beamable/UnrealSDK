#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventPlayerView.h"

#include "EventPlayerViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventPlayerViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventPlayerView To JSON String")
	static FString EventPlayerViewToJsonString(const UEventPlayerView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventPlayerView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventPlayerView* Make(TArray<UEventPlayerStateView*> Running, TArray<UEventPlayerStateView*> Done, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventPlayerView", meta=(NativeBreakFunc))
	static void Break(const UEventPlayerView* Serializable, TArray<UEventPlayerStateView*>& Running, TArray<UEventPlayerStateView*>& Done);
};