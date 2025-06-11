#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeleteDevicesRequestBody.h"

#include "DeleteDevicesRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteDevicesRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="DeleteDevicesRequestBody To JSON String")
	static FString DeleteDevicesRequestBodyToJsonString(const UDeleteDevicesRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make DeleteDevicesRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="DeviceIds, Outer", NativeMakeFunc))
	static UDeleteDevicesRequestBody* Make(FOptionalArrayOfString DeviceIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break DeleteDevicesRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeleteDevicesRequestBody* Serializable, FOptionalArrayOfString& DeviceIds);
};