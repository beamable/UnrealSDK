#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventClaimResponse.h"

#include "EventClaimResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventClaimResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="EventClaimResponse To JSON String")
	static FString EventClaimResponseToJsonString(const UEventClaimResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make EventClaimResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventClaimResponse* Make(UEventPlayerStateView* View, FString GameRspJson, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break EventClaimResponse", meta=(NativeBreakFunc))
	static void Break(const UEventClaimResponse* Serializable, UEventPlayerStateView*& View, FString& GameRspJson);
};