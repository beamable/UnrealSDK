
#pragma once

#include "CoreMinimal.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceJoinNumbersAsStringRequestArgs.h"

#include "StandaloneMicroserviceJoinNumbersAsStringRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UStandaloneMicroserviceJoinNumbersAsStringRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StandaloneMicroserviceJoinNumbersAsStringRequestArgs To JSON String")
	static FString StandaloneMicroserviceJoinNumbersAsStringRequestArgsToJsonString(const UStandaloneMicroserviceJoinNumbersAsStringRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StandaloneMicroserviceJoinNumbersAsStringRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStandaloneMicroserviceJoinNumbersAsStringRequestArgs* Make(int32 A, int32 B, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StandaloneMicroserviceJoinNumbersAsStringRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UStandaloneMicroserviceJoinNumbersAsStringRequestArgs* Serializable, int32& A, int32& B);
};