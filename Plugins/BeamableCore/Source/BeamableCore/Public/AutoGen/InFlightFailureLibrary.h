#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/InFlightFailure.h"

#include "InFlightFailureLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInFlightFailureLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Json", DisplayName="InFlightFailure To JSON String")
	static FString InFlightFailureToJsonString(const UInFlightFailure* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Make/Break", DisplayName="Make InFlightFailure", meta=(DefaultToSelf="Outer", AdvancedDisplay="Timestamp, Outer", NativeMakeFunc))
	static UInFlightFailure* Make(FString Id, FString ServiceObjectId, FString ServiceName, UInFlightMessage* InFlightMessage, FString LastError, FOptionalDateTime Timestamp, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Make/Break", DisplayName="Break InFlightFailure", meta=(NativeBreakFunc))
	static void Break(const UInFlightFailure* Serializable, FString& Id, FString& ServiceObjectId, FString& ServiceName, UInFlightMessage*& InFlightMessage, FString& LastError, FOptionalDateTime& Timestamp);
};