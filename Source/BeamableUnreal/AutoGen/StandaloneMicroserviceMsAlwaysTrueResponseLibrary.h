
#pragma once

#include "CoreMinimal.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAlwaysTrueResponse.h"

#include "StandaloneMicroserviceMsAlwaysTrueResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UStandaloneMicroserviceMsAlwaysTrueResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StandaloneMicroserviceMsAlwaysTrueResponse To JSON String")
	static FString StandaloneMicroserviceMsAlwaysTrueResponseToJsonString(const UStandaloneMicroserviceMsAlwaysTrueResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StandaloneMicroserviceMsAlwaysTrueResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStandaloneMicroserviceMsAlwaysTrueResponse* Make(bool bValue, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StandaloneMicroserviceMsAlwaysTrueResponse", meta=(NativeBreakFunc))
	static void Break(const UStandaloneMicroserviceMsAlwaysTrueResponse* Serializable, bool& bValue);
};