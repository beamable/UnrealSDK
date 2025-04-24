#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventPhaseRuntime.h"

#include "EventPhaseRuntimeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventPhaseRuntimeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventPhaseRuntime To JSON String")
	static FString EventPhaseRuntimeToJsonString(const UEventPhaseRuntime* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventPhaseRuntime", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventPhaseRuntime* Make(FString Name, int64 StartTime, int64 EndTime, TArray<UEventRule*> Rules, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventPhaseRuntime", meta=(NativeBreakFunc))
	static void Break(const UEventPhaseRuntime* Serializable, FString& Name, int64& StartTime, int64& EndTime, TArray<UEventRule*>& Rules);
};