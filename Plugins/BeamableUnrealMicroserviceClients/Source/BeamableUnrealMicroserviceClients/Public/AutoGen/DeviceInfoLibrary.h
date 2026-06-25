#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeviceInfo.h"

#include "DeviceInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDeviceInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="DeviceInfo To JSON String")
	static FString DeviceInfoToJsonString(const UDeviceInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make DeviceInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeviceInfo* Make(FString Token, FString Platform, FString Environment, int64 UpdatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break DeviceInfo", meta=(NativeBreakFunc))
	static void Break(const UDeviceInfo* Serializable, FString& Token, FString& Platform, FString& Environment, int64& UpdatedAt);
};