#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventPhase.h"

#include "EventPhaseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventPhaseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|4 - Json", DisplayName="EventPhase To JSON String")
	static FString EventPhaseToJsonString(const UEventPhase* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|3 - Backend", DisplayName="Make EventPhase", meta=(DefaultToSelf="Outer", AdvancedDisplay="Rules, Outer", NativeMakeFunc))
	static UEventPhase* Make(FString Name, int32 DurationMinutes, int64 DurationMillis, int64 DurationSeconds, FOptionalArrayOfEventRule Rules, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|3 - Backend", DisplayName="Break EventPhase", meta=(NativeBreakFunc))
	static void Break(const UEventPhase* Serializable, FString& Name, int32& DurationMinutes, int64& DurationMillis, int64& DurationSeconds, FOptionalArrayOfEventRule& Rules);
};