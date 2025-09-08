#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AdminActorInFlightFailure.h"

#include "AdminActorInFlightFailureLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAdminActorInFlightFailureLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Json", DisplayName="AdminActorInFlightFailure To JSON String")
	static FString AdminActorInFlightFailureToJsonString(const UAdminActorInFlightFailure* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Make/Break", DisplayName="Make AdminActorInFlightFailure", meta=(DefaultToSelf="Outer", AdvancedDisplay="Timestamp, Outer", NativeMakeFunc))
	static UAdminActorInFlightFailure* Make(FString FailureId, FString ServiceObjectId, FString ServiceName, UAdminActorInFlightMessage* InFlightMessage, FString LastError, FOptionalDateTime Timestamp, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Admin|Utils|Make/Break", DisplayName="Break AdminActorInFlightFailure", meta=(NativeBreakFunc))
	static void Break(const UAdminActorInFlightFailure* Serializable, FString& FailureId, FString& ServiceObjectId, FString& ServiceName, UAdminActorInFlightMessage*& InFlightMessage, FString& LastError, FOptionalDateTime& Timestamp);
};