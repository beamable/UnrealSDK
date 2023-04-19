
#pragma once

#include "CoreMinimal.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAddResponse.h"

#include "StandaloneMicroserviceMsAddResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UStandaloneMicroserviceMsAddResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StandaloneMicroserviceMsAddResponse To JSON String")
	static FString StandaloneMicroserviceMsAddResponseToJsonString(const UStandaloneMicroserviceMsAddResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StandaloneMicroserviceMsAddResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStandaloneMicroserviceMsAddResponse* Make(int32 Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StandaloneMicroserviceMsAddResponse", meta=(NativeBreakFunc))
	static void Break(const UStandaloneMicroserviceMsAddResponse* Serializable, int32& Value);
};