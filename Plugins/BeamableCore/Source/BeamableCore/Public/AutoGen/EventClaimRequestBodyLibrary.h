#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventClaimRequestBody.h"

#include "EventClaimRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventClaimRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Json", DisplayName="EventClaimRequestBody To JSON String")
	static FString EventClaimRequestBodyToJsonString(const UEventClaimRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make EventClaimRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventClaimRequestBody* Make(FString EventId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Break EventClaimRequestBody", meta=(NativeBreakFunc))
	static void Break(const UEventClaimRequestBody* Serializable, FString& EventId);
};