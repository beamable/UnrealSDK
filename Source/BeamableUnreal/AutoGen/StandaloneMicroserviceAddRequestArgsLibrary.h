
#pragma once

#include "CoreMinimal.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceAddRequestArgs.h"

#include "StandaloneMicroserviceAddRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UStandaloneMicroserviceAddRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StandaloneMicroserviceAddRequestArgs To JSON String")
	static FString StandaloneMicroserviceAddRequestArgsToJsonString(const UStandaloneMicroserviceAddRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StandaloneMicroserviceAddRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStandaloneMicroserviceAddRequestArgs* Make(int32 A, int32 B, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StandaloneMicroserviceAddRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UStandaloneMicroserviceAddRequestArgs* Serializable, int32& A, int32& B);
};