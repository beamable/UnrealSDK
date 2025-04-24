#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeviceIdAvailableRequestBody.h"

#include "DeviceIdAvailableRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeviceIdAvailableRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="DeviceIdAvailableRequestBody To JSON String")
	static FString DeviceIdAvailableRequestBodyToJsonString(const UDeviceIdAvailableRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make DeviceIdAvailableRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeviceIdAvailableRequestBody* Make(FString DeviceId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break DeviceIdAvailableRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeviceIdAvailableRequestBody* Serializable, FString& DeviceId);
};