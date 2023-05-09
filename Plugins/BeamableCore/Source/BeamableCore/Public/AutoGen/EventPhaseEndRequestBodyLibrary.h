#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventPhaseEndRequestBody.h"

#include "EventPhaseEndRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventPhaseEndRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventPhaseEndRequestBody To JSON String")
	static FString EventPhaseEndRequestBodyToJsonString(const UEventPhaseEndRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventPhaseEndRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Time, Outer", NativeMakeFunc))
	static UEventPhaseEndRequestBody* Make(FOptionalString Time, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventPhaseEndRequestBody", meta=(NativeBreakFunc))
	static void Break(const UEventPhaseEndRequestBody* Serializable, FOptionalString& Time);
};