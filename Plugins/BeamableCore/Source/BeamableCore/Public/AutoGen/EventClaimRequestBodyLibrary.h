#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventClaimRequestBody.h"

#include "EventClaimRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventClaimRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventClaimRequestBody To JSON String")
	static FString EventClaimRequestBodyToJsonString(const UEventClaimRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventClaimRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventClaimRequestBody* Make(FString EventId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventClaimRequestBody", meta=(NativeBreakFunc))
	static void Break(const UEventClaimRequestBody* Serializable, FString& EventId);
};