#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventPhaseTime.h"

#include "EventPhaseTimeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventPhaseTimeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventPhaseTime To JSON String")
	static FString EventPhaseTimeToJsonString(const UEventPhaseTime* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventPhaseTime", meta=(DefaultToSelf="Outer", AdvancedDisplay="StartTime, EndTime, Outer", NativeMakeFunc))
	static UEventPhaseTime* Make(FString Name, FOptionalInt64 StartTime, FOptionalInt64 EndTime, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventPhaseTime", meta=(NativeBreakFunc))
	static void Break(const UEventPhaseTime* Serializable, FString& Name, FOptionalInt64& StartTime, FOptionalInt64& EndTime);
};