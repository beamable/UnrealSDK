#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeviceIdAvailableRequestBody.h"

#include "DeviceIdAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeviceIdAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - DeviceIdAvailableRequestBody To JSON String")
	static FString DeviceIdAvailableRequestBodyToJsonString(const UDeviceIdAvailableRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make DeviceIdAvailableRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeviceIdAvailableRequestBody* Make(FString DeviceId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break DeviceIdAvailableRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeviceIdAvailableRequestBody* Serializable, FString& DeviceId);
};