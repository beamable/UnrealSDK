#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UnregisterDeviceTokenRequestArgs.h"

#include "UnregisterDeviceTokenRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UUnregisterDeviceTokenRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="UnregisterDeviceTokenRequestArgs To JSON String")
	static FString UnregisterDeviceTokenRequestArgsToJsonString(const UUnregisterDeviceTokenRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make UnregisterDeviceTokenRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UUnregisterDeviceTokenRequestArgs* Make(FString Token, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break UnregisterDeviceTokenRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UUnregisterDeviceTokenRequestArgs* Serializable, FString& Token);
};