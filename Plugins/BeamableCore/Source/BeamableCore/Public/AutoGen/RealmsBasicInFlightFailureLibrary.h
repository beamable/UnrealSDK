#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicInFlightFailure.h"

#include "RealmsBasicInFlightFailureLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicInFlightFailureLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicInFlightFailure To JSON String")
	static FString RealmsBasicInFlightFailureToJsonString(const URealmsBasicInFlightFailure* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicInFlightFailure", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmsBasicInFlightFailure* Make(FString ServiceObjectId, int64 Timestamp, FString ServiceName, URealmsBasicInFlightMessage* InFlightMessage, FString LastError, FString Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicInFlightFailure", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicInFlightFailure* Serializable, FString& ServiceObjectId, int64& Timestamp, FString& ServiceName, URealmsBasicInFlightMessage*& InFlightMessage, FString& LastError, FString& Id);
};