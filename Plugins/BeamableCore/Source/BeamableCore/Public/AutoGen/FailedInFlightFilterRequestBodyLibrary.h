#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FailedInFlightFilterRequestBody.h"

#include "FailedInFlightFilterRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFailedInFlightFilterRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="FailedInFlightFilterRequestBody To JSON String")
	static FString FailedInFlightFilterRequestBodyToJsonString(const UFailedInFlightFilterRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make FailedInFlightFilterRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ServiceObjectId, Outer", NativeMakeFunc))
	static UFailedInFlightFilterRequestBody* Make(FString ServiceName, FOptionalString ServiceObjectId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break FailedInFlightFilterRequestBody", meta=(NativeBreakFunc))
	static void Break(const UFailedInFlightFilterRequestBody* Serializable, FString& ServiceName, FOptionalString& ServiceObjectId);
};