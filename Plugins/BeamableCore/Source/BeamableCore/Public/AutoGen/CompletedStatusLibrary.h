#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CompletedStatus.h"

#include "CompletedStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCompletedStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="CompletedStatus To JSON String")
	static FString CompletedStatusToJsonString(const UCompletedStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make CompletedStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCompletedStatus* Make(int32 Cycle, int32 Tier, int32 Stage, int32 Delta, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break CompletedStatus", meta=(NativeBreakFunc))
	static void Break(const UCompletedStatus* Serializable, int32& Cycle, int32& Tier, int32& Stage, int32& Delta);
};