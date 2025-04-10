#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OnlineStatusResponses.h"

#include "OnlineStatusResponsesLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOnlineStatusResponsesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="OnlineStatusResponses To JSON String")
	static FString OnlineStatusResponsesToJsonString(const UOnlineStatusResponses* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make OnlineStatusResponses", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UOnlineStatusResponses* Make(TArray<UPlayerOnlineStatusResponse*> Players, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break OnlineStatusResponses", meta=(NativeBreakFunc))
	static void Break(const UOnlineStatusResponses* Serializable, TArray<UPlayerOnlineStatusResponse*>& Players);
};