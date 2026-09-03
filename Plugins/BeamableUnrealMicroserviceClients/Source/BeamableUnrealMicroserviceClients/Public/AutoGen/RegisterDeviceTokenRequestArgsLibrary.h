#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterDeviceTokenRequestArgs.h"

#include "RegisterDeviceTokenRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API URegisterDeviceTokenRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="RegisterDeviceTokenRequestArgs To JSON String")
	static FString RegisterDeviceTokenRequestArgsToJsonString(const URegisterDeviceTokenRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make RegisterDeviceTokenRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URegisterDeviceTokenRequestArgs* Make(FString Token, FString Environment, FString Platform, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break RegisterDeviceTokenRequestArgs", meta=(NativeBreakFunc))
	static void Break(const URegisterDeviceTokenRequestArgs* Serializable, FString& Token, FString& Environment, FString& Platform);
};