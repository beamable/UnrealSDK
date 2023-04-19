
#pragma once

#include "CoreMinimal.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsJoinNumbersAsStringResponse.h"

#include "StandaloneMicroserviceMsJoinNumbersAsStringResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UStandaloneMicroserviceMsJoinNumbersAsStringResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StandaloneMicroserviceMsJoinNumbersAsStringResponse To JSON String")
	static FString StandaloneMicroserviceMsJoinNumbersAsStringResponseToJsonString(const UStandaloneMicroserviceMsJoinNumbersAsStringResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StandaloneMicroserviceMsJoinNumbersAsStringResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStandaloneMicroserviceMsJoinNumbersAsStringResponse* Make(FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StandaloneMicroserviceMsJoinNumbersAsStringResponse", meta=(NativeBreakFunc))
	static void Break(const UStandaloneMicroserviceMsJoinNumbersAsStringResponse* Serializable, FString& Value);
};