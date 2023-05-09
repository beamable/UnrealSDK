#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventClaimResponse.h"

#include "EventClaimResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventClaimResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventClaimResponse To JSON String")
	static FString EventClaimResponseToJsonString(const UEventClaimResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventClaimResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventClaimResponse* Make(UEventPlayerStateView* View, FString GameRspJson, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventClaimResponse", meta=(NativeBreakFunc))
	static void Break(const UEventClaimResponse* Serializable, UEventPlayerStateView*& View, FString& GameRspJson);
};