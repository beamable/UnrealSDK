#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AvailabilityResponse.h"

#include "AvailabilityResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAvailabilityResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AvailabilityResponse To JSON String")
	static FString AvailabilityResponseToJsonString(const UAvailabilityResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AvailabilityResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAvailabilityResponse* Make(bool bName, bool bTag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AvailabilityResponse", meta=(NativeBreakFunc))
	static void Break(const UAvailabilityResponse* Serializable, bool& bName, bool& bTag);
};