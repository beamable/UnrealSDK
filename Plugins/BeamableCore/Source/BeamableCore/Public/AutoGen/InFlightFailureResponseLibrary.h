#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InFlightFailureResponse.h"

#include "InFlightFailureResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInFlightFailureResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="InFlightFailureResponse To JSON String")
	static FString InFlightFailureResponseToJsonString(const UInFlightFailureResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make InFlightFailureResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UInFlightFailureResponse* Make(TArray<UInFlightFailure*> Failures, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break InFlightFailureResponse", meta=(NativeBreakFunc))
	static void Break(const UInFlightFailureResponse* Serializable, TArray<UInFlightFailure*>& Failures);
};