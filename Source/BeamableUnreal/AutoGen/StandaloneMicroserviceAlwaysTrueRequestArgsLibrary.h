
#pragma once

#include "CoreMinimal.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceAlwaysTrueRequestArgs.h"

#include "StandaloneMicroserviceAlwaysTrueRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UStandaloneMicroserviceAlwaysTrueRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StandaloneMicroserviceAlwaysTrueRequestArgs To JSON String")
	static FString StandaloneMicroserviceAlwaysTrueRequestArgsToJsonString(const UStandaloneMicroserviceAlwaysTrueRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StandaloneMicroserviceAlwaysTrueRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStandaloneMicroserviceAlwaysTrueRequestArgs* Make(FString Text, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StandaloneMicroserviceAlwaysTrueRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UStandaloneMicroserviceAlwaysTrueRequestArgs* Serializable, FString& Text);
};